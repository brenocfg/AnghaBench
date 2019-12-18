#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct TYPE_16__ {void* new_xmax; scalar_t__ new_offnum; int /*<<< orphan*/  old_infobits_set; void* old_xmax; scalar_t__ old_offnum; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ xl_heap_update ;
struct TYPE_17__ {scalar_t__ t_hoff; int /*<<< orphan*/  t_infomask; int /*<<< orphan*/  t_infomask2; } ;
typedef  TYPE_3__ xl_heap_header ;
typedef  int /*<<< orphan*/  uint8 ;
typedef  size_t uint16 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_19__ {int t_len; TYPE_13__* t_data; int /*<<< orphan*/  t_self; } ;
struct TYPE_18__ {TYPE_1__* rd_rel; } ;
struct TYPE_15__ {scalar_t__ relreplident; } ;
struct TYPE_14__ {int t_hoff; int /*<<< orphan*/  t_infomask; int /*<<< orphan*/  t_infomask2; } ;
typedef  TYPE_4__* Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_5__* HeapTuple ;
typedef  scalar_t__ Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 scalar_t__ FirstOffsetNumber ; 
 void* HeapTupleHeaderGetRawXmax (TYPE_13__*) ; 
 scalar_t__ HeapTupleIsHeapOnly (TYPE_5__*) ; 
 scalar_t__ ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 size_t Min (int,int) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int REGBUF_KEEP_DATA ; 
 int REGBUF_STANDARD ; 
 int REGBUF_WILL_INIT ; 
 scalar_t__ REPLICA_IDENTITY_FULL ; 
 int /*<<< orphan*/  RM_HEAP_ID ; 
 int RelationIsLogicallyLogged (TYPE_4__*) ; 
 int RelationNeedsWAL (TYPE_4__*) ; 
 scalar_t__ SizeOfHeapHeader ; 
 scalar_t__ SizeOfHeapUpdate ; 
 scalar_t__ SizeofHeapTupleHeader ; 
 int /*<<< orphan*/  XLH_UPDATE_CONTAINS_NEW_TUPLE ; 
 int /*<<< orphan*/  XLH_UPDATE_CONTAINS_OLD_KEY ; 
 int /*<<< orphan*/  XLH_UPDATE_CONTAINS_OLD_TUPLE ; 
 int /*<<< orphan*/  XLH_UPDATE_NEW_ALL_VISIBLE_CLEARED ; 
 int /*<<< orphan*/  XLH_UPDATE_OLD_ALL_VISIBLE_CLEARED ; 
 int /*<<< orphan*/  XLH_UPDATE_PREFIX_FROM_OLD ; 
 int /*<<< orphan*/  XLH_UPDATE_SUFFIX_FROM_OLD ; 
 int /*<<< orphan*/  XLOG_HEAP_HOT_UPDATE ; 
 int /*<<< orphan*/  XLOG_HEAP_INIT_PAGE ; 
 int /*<<< orphan*/  XLOG_HEAP_UPDATE ; 
 int /*<<< orphan*/  XLOG_INCLUDE_ORIGIN ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogCheckBufferNeedsBackup (scalar_t__) ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,scalar_t__,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,scalar_t__) ; 
 int /*<<< orphan*/  XLogSetRecordFlags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_infobits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static XLogRecPtr
log_heap_update(Relation reln, Buffer oldbuf,
				Buffer newbuf, HeapTuple oldtup, HeapTuple newtup,
				HeapTuple old_key_tuple,
				bool all_visible_cleared, bool new_all_visible_cleared)
{
	xl_heap_update xlrec;
	xl_heap_header xlhdr;
	xl_heap_header xlhdr_idx;
	uint8		info;
	uint16		prefix_suffix[2];
	uint16		prefixlen = 0,
				suffixlen = 0;
	XLogRecPtr	recptr;
	Page		page = BufferGetPage(newbuf);
	bool		need_tuple_data = RelationIsLogicallyLogged(reln);
	bool		init;
	int			bufflags;

	/* Caller should not call me on a non-WAL-logged relation */
	Assert(RelationNeedsWAL(reln));

	XLogBeginInsert();

	if (HeapTupleIsHeapOnly(newtup))
		info = XLOG_HEAP_HOT_UPDATE;
	else
		info = XLOG_HEAP_UPDATE;

	/*
	 * If the old and new tuple are on the same page, we only need to log the
	 * parts of the new tuple that were changed.  That saves on the amount of
	 * WAL we need to write.  Currently, we just count any unchanged bytes in
	 * the beginning and end of the tuple.  That's quick to check, and
	 * perfectly covers the common case that only one field is updated.
	 *
	 * We could do this even if the old and new tuple are on different pages,
	 * but only if we don't make a full-page image of the old page, which is
	 * difficult to know in advance.  Also, if the old tuple is corrupt for
	 * some reason, it would allow the corruption to propagate the new page,
	 * so it seems best to avoid.  Under the general assumption that most
	 * updates tend to create the new tuple version on the same page, there
	 * isn't much to be gained by doing this across pages anyway.
	 *
	 * Skip this if we're taking a full-page image of the new page, as we
	 * don't include the new tuple in the WAL record in that case.  Also
	 * disable if wal_level='logical', as logical decoding needs to be able to
	 * read the new tuple in whole from the WAL record alone.
	 */
	if (oldbuf == newbuf && !need_tuple_data &&
		!XLogCheckBufferNeedsBackup(newbuf))
	{
		char	   *oldp = (char *) oldtup->t_data + oldtup->t_data->t_hoff;
		char	   *newp = (char *) newtup->t_data + newtup->t_data->t_hoff;
		int			oldlen = oldtup->t_len - oldtup->t_data->t_hoff;
		int			newlen = newtup->t_len - newtup->t_data->t_hoff;

		/* Check for common prefix between old and new tuple */
		for (prefixlen = 0; prefixlen < Min(oldlen, newlen); prefixlen++)
		{
			if (newp[prefixlen] != oldp[prefixlen])
				break;
		}

		/*
		 * Storing the length of the prefix takes 2 bytes, so we need to save
		 * at least 3 bytes or there's no point.
		 */
		if (prefixlen < 3)
			prefixlen = 0;

		/* Same for suffix */
		for (suffixlen = 0; suffixlen < Min(oldlen, newlen) - prefixlen; suffixlen++)
		{
			if (newp[newlen - suffixlen - 1] != oldp[oldlen - suffixlen - 1])
				break;
		}
		if (suffixlen < 3)
			suffixlen = 0;
	}

	/* Prepare main WAL data chain */
	xlrec.flags = 0;
	if (all_visible_cleared)
		xlrec.flags |= XLH_UPDATE_OLD_ALL_VISIBLE_CLEARED;
	if (new_all_visible_cleared)
		xlrec.flags |= XLH_UPDATE_NEW_ALL_VISIBLE_CLEARED;
	if (prefixlen > 0)
		xlrec.flags |= XLH_UPDATE_PREFIX_FROM_OLD;
	if (suffixlen > 0)
		xlrec.flags |= XLH_UPDATE_SUFFIX_FROM_OLD;
	if (need_tuple_data)
	{
		xlrec.flags |= XLH_UPDATE_CONTAINS_NEW_TUPLE;
		if (old_key_tuple)
		{
			if (reln->rd_rel->relreplident == REPLICA_IDENTITY_FULL)
				xlrec.flags |= XLH_UPDATE_CONTAINS_OLD_TUPLE;
			else
				xlrec.flags |= XLH_UPDATE_CONTAINS_OLD_KEY;
		}
	}

	/* If new tuple is the single and first tuple on page... */
	if (ItemPointerGetOffsetNumber(&(newtup->t_self)) == FirstOffsetNumber &&
		PageGetMaxOffsetNumber(page) == FirstOffsetNumber)
	{
		info |= XLOG_HEAP_INIT_PAGE;
		init = true;
	}
	else
		init = false;

	/* Prepare WAL data for the old page */
	xlrec.old_offnum = ItemPointerGetOffsetNumber(&oldtup->t_self);
	xlrec.old_xmax = HeapTupleHeaderGetRawXmax(oldtup->t_data);
	xlrec.old_infobits_set = compute_infobits(oldtup->t_data->t_infomask,
											  oldtup->t_data->t_infomask2);

	/* Prepare WAL data for the new page */
	xlrec.new_offnum = ItemPointerGetOffsetNumber(&newtup->t_self);
	xlrec.new_xmax = HeapTupleHeaderGetRawXmax(newtup->t_data);

	bufflags = REGBUF_STANDARD;
	if (init)
		bufflags |= REGBUF_WILL_INIT;
	if (need_tuple_data)
		bufflags |= REGBUF_KEEP_DATA;

	XLogRegisterBuffer(0, newbuf, bufflags);
	if (oldbuf != newbuf)
		XLogRegisterBuffer(1, oldbuf, REGBUF_STANDARD);

	XLogRegisterData((char *) &xlrec, SizeOfHeapUpdate);

	/*
	 * Prepare WAL data for the new tuple.
	 */
	if (prefixlen > 0 || suffixlen > 0)
	{
		if (prefixlen > 0 && suffixlen > 0)
		{
			prefix_suffix[0] = prefixlen;
			prefix_suffix[1] = suffixlen;
			XLogRegisterBufData(0, (char *) &prefix_suffix, sizeof(uint16) * 2);
		}
		else if (prefixlen > 0)
		{
			XLogRegisterBufData(0, (char *) &prefixlen, sizeof(uint16));
		}
		else
		{
			XLogRegisterBufData(0, (char *) &suffixlen, sizeof(uint16));
		}
	}

	xlhdr.t_infomask2 = newtup->t_data->t_infomask2;
	xlhdr.t_infomask = newtup->t_data->t_infomask;
	xlhdr.t_hoff = newtup->t_data->t_hoff;
	Assert(SizeofHeapTupleHeader + prefixlen + suffixlen <= newtup->t_len);

	/*
	 * PG73FORMAT: write bitmap [+ padding] [+ oid] + data
	 *
	 * The 'data' doesn't include the common prefix or suffix.
	 */
	XLogRegisterBufData(0, (char *) &xlhdr, SizeOfHeapHeader);
	if (prefixlen == 0)
	{
		XLogRegisterBufData(0,
							((char *) newtup->t_data) + SizeofHeapTupleHeader,
							newtup->t_len - SizeofHeapTupleHeader - suffixlen);
	}
	else
	{
		/*
		 * Have to write the null bitmap and data after the common prefix as
		 * two separate rdata entries.
		 */
		/* bitmap [+ padding] [+ oid] */
		if (newtup->t_data->t_hoff - SizeofHeapTupleHeader > 0)
		{
			XLogRegisterBufData(0,
								((char *) newtup->t_data) + SizeofHeapTupleHeader,
								newtup->t_data->t_hoff - SizeofHeapTupleHeader);
		}

		/* data after common prefix */
		XLogRegisterBufData(0,
							((char *) newtup->t_data) + newtup->t_data->t_hoff + prefixlen,
							newtup->t_len - newtup->t_data->t_hoff - prefixlen - suffixlen);
	}

	/* We need to log a tuple identity */
	if (need_tuple_data && old_key_tuple)
	{
		/* don't really need this, but its more comfy to decode */
		xlhdr_idx.t_infomask2 = old_key_tuple->t_data->t_infomask2;
		xlhdr_idx.t_infomask = old_key_tuple->t_data->t_infomask;
		xlhdr_idx.t_hoff = old_key_tuple->t_data->t_hoff;

		XLogRegisterData((char *) &xlhdr_idx, SizeOfHeapHeader);

		/* PG73FORMAT: write bitmap [+ padding] [+ oid] + data */
		XLogRegisterData((char *) old_key_tuple->t_data + SizeofHeapTupleHeader,
						 old_key_tuple->t_len - SizeofHeapTupleHeader);
	}

	/* filtering by origin on a row level is much more efficient */
	XLogSetRecordFlags(XLOG_INCLUDE_ORIGIN);

	recptr = XLogInsert(RM_HEAP_ID, info);

	return recptr;
}