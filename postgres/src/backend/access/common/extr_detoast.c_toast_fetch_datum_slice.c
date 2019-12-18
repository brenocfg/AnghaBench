#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct varlena {int dummy; } ;
struct varatt_external {int va_extsize; int /*<<< orphan*/  va_valueid; int /*<<< orphan*/  va_toastrelid; } ;
typedef  int int32 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_10__ {int /*<<< orphan*/  rd_att; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  SnapshotData ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_1__* Relation ;
typedef  struct varlena* Pointer ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  BTGreaterEqualStrategyNumber ; 
 int /*<<< orphan*/  BTLessEqualStrategyNumber ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 struct varlena* DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_INT4GE ; 
 int /*<<< orphan*/  F_INT4LE ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_VARSIZE (struct varlena*,int) ; 
 int /*<<< orphan*/  SET_VARSIZE_COMPRESSED (struct varlena*,int) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TOAST_MAX_CHUNK_SIZE ; 
 int /*<<< orphan*/  VARATT_EXTERNAL_GET_POINTER (struct varatt_external,struct varlena*) ; 
 scalar_t__ VARATT_EXTERNAL_IS_COMPRESSED (struct varatt_external) ; 
 int /*<<< orphan*/  VARATT_IS_EXTENDED (struct varlena*) ; 
 int /*<<< orphan*/  VARATT_IS_EXTERNAL_ONDISK (struct varlena*) ; 
 scalar_t__ VARATT_IS_SHORT (struct varlena*) ; 
 char* VARDATA (struct varlena*) ; 
 char* VARDATA_SHORT (struct varlena*) ; 
 int VARHDRSZ ; 
 int VARHDRSZ_SHORT ; 
 int VARSIZE (struct varlena*) ; 
 int VARSIZE_SHORT (struct varlena*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fastgetattr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  init_toast_snapshot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  systable_beginscan_ordered (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan_ordered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_getnext_ordered (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toast_close_indexes (TYPE_1__**,int,int /*<<< orphan*/ ) ; 
 int toast_open_indexes (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__***,int*) ; 

__attribute__((used)) static struct varlena *
toast_fetch_datum_slice(struct varlena *attr, int32 sliceoffset, int32 length)
{
	Relation	toastrel;
	Relation   *toastidxs;
	ScanKeyData toastkey[3];
	int			nscankeys;
	SysScanDesc toastscan;
	HeapTuple	ttup;
	TupleDesc	toasttupDesc;
	struct varlena *result;
	struct varatt_external toast_pointer;
	int32		attrsize;
	int32		residx;
	int32		nextidx;
	int			numchunks;
	int			startchunk;
	int			endchunk;
	int32		startoffset;
	int32		endoffset;
	int			totalchunks;
	Pointer		chunk;
	bool		isnull;
	char	   *chunkdata;
	int32		chunksize;
	int32		chcpystrt;
	int32		chcpyend;
	int			num_indexes;
	int			validIndex;
	SnapshotData SnapshotToast;

	if (!VARATT_IS_EXTERNAL_ONDISK(attr))
		elog(ERROR, "toast_fetch_datum_slice shouldn't be called for non-ondisk datums");

	/* Must copy to access aligned fields */
	VARATT_EXTERNAL_GET_POINTER(toast_pointer, attr);

	/*
	 * It's nonsense to fetch slices of a compressed datum unless when it's
	 * a prefix -- this isn't lo_* we can't return a compressed datum which
	 * is meaningful to toast later.
	 */
	Assert(!VARATT_EXTERNAL_IS_COMPRESSED(toast_pointer) || 0 == sliceoffset);

	attrsize = toast_pointer.va_extsize;
	totalchunks = ((attrsize - 1) / TOAST_MAX_CHUNK_SIZE) + 1;

	if (sliceoffset >= attrsize)
	{
		sliceoffset = 0;
		length = 0;
	}

	/*
	 * When fetching a prefix of a compressed external datum, account for the
	 * rawsize tracking amount of raw data, which is stored at the beginning
	 * as an int32 value).
	 */
	if (VARATT_EXTERNAL_IS_COMPRESSED(toast_pointer) && length > 0)
		length = length + sizeof(int32);

	if (((sliceoffset + length) > attrsize) || length < 0)
		length = attrsize - sliceoffset;

	result = (struct varlena *) palloc(length + VARHDRSZ);

	if (VARATT_EXTERNAL_IS_COMPRESSED(toast_pointer))
		SET_VARSIZE_COMPRESSED(result, length + VARHDRSZ);
	else
		SET_VARSIZE(result, length + VARHDRSZ);

	if (length == 0)
		return result;			/* Can save a lot of work at this point! */

	startchunk = sliceoffset / TOAST_MAX_CHUNK_SIZE;
	endchunk = (sliceoffset + length - 1) / TOAST_MAX_CHUNK_SIZE;
	numchunks = (endchunk - startchunk) + 1;

	startoffset = sliceoffset % TOAST_MAX_CHUNK_SIZE;
	endoffset = (sliceoffset + length - 1) % TOAST_MAX_CHUNK_SIZE;

	/*
	 * Open the toast relation and its indexes
	 */
	toastrel = table_open(toast_pointer.va_toastrelid, AccessShareLock);
	toasttupDesc = toastrel->rd_att;

	/* Look for the valid index of toast relation */
	validIndex = toast_open_indexes(toastrel,
									AccessShareLock,
									&toastidxs,
									&num_indexes);

	/*
	 * Setup a scan key to fetch from the index. This is either two keys or
	 * three depending on the number of chunks.
	 */
	ScanKeyInit(&toastkey[0],
				(AttrNumber) 1,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(toast_pointer.va_valueid));

	/*
	 * Use equality condition for one chunk, a range condition otherwise:
	 */
	if (numchunks == 1)
	{
		ScanKeyInit(&toastkey[1],
					(AttrNumber) 2,
					BTEqualStrategyNumber, F_INT4EQ,
					Int32GetDatum(startchunk));
		nscankeys = 2;
	}
	else
	{
		ScanKeyInit(&toastkey[1],
					(AttrNumber) 2,
					BTGreaterEqualStrategyNumber, F_INT4GE,
					Int32GetDatum(startchunk));
		ScanKeyInit(&toastkey[2],
					(AttrNumber) 2,
					BTLessEqualStrategyNumber, F_INT4LE,
					Int32GetDatum(endchunk));
		nscankeys = 3;
	}

	/*
	 * Read the chunks by index
	 *
	 * The index is on (valueid, chunkidx) so they will come in order
	 */
	init_toast_snapshot(&SnapshotToast);
	nextidx = startchunk;
	toastscan = systable_beginscan_ordered(toastrel, toastidxs[validIndex],
										   &SnapshotToast, nscankeys, toastkey);
	while ((ttup = systable_getnext_ordered(toastscan, ForwardScanDirection)) != NULL)
	{
		/*
		 * Have a chunk, extract the sequence number and the data
		 */
		residx = DatumGetInt32(fastgetattr(ttup, 2, toasttupDesc, &isnull));
		Assert(!isnull);
		chunk = DatumGetPointer(fastgetattr(ttup, 3, toasttupDesc, &isnull));
		Assert(!isnull);
		if (!VARATT_IS_EXTENDED(chunk))
		{
			chunksize = VARSIZE(chunk) - VARHDRSZ;
			chunkdata = VARDATA(chunk);
		}
		else if (VARATT_IS_SHORT(chunk))
		{
			/* could happen due to heap_form_tuple doing its thing */
			chunksize = VARSIZE_SHORT(chunk) - VARHDRSZ_SHORT;
			chunkdata = VARDATA_SHORT(chunk);
		}
		else
		{
			/* should never happen */
			elog(ERROR, "found toasted toast chunk for toast value %u in %s",
				 toast_pointer.va_valueid,
				 RelationGetRelationName(toastrel));
			chunksize = 0;		/* keep compiler quiet */
			chunkdata = NULL;
		}

		/*
		 * Some checks on the data we've found
		 */
		if ((residx != nextidx) || (residx > endchunk) || (residx < startchunk))
			elog(ERROR, "unexpected chunk number %d (expected %d) for toast value %u in %s",
				 residx, nextidx,
				 toast_pointer.va_valueid,
				 RelationGetRelationName(toastrel));
		if (residx < totalchunks - 1)
		{
			if (chunksize != TOAST_MAX_CHUNK_SIZE)
				elog(ERROR, "unexpected chunk size %d (expected %d) in chunk %d of %d for toast value %u in %s when fetching slice",
					 chunksize, (int) TOAST_MAX_CHUNK_SIZE,
					 residx, totalchunks,
					 toast_pointer.va_valueid,
					 RelationGetRelationName(toastrel));
		}
		else if (residx == totalchunks - 1)
		{
			if ((residx * TOAST_MAX_CHUNK_SIZE + chunksize) != attrsize)
				elog(ERROR, "unexpected chunk size %d (expected %d) in final chunk %d for toast value %u in %s when fetching slice",
					 chunksize,
					 (int) (attrsize - residx * TOAST_MAX_CHUNK_SIZE),
					 residx,
					 toast_pointer.va_valueid,
					 RelationGetRelationName(toastrel));
		}
		else
			elog(ERROR, "unexpected chunk number %d (out of range %d..%d) for toast value %u in %s",
				 residx,
				 0, totalchunks - 1,
				 toast_pointer.va_valueid,
				 RelationGetRelationName(toastrel));

		/*
		 * Copy the data into proper place in our result
		 */
		chcpystrt = 0;
		chcpyend = chunksize - 1;
		if (residx == startchunk)
			chcpystrt = startoffset;
		if (residx == endchunk)
			chcpyend = endoffset;

		memcpy(VARDATA(result) +
			   (residx * TOAST_MAX_CHUNK_SIZE - sliceoffset) + chcpystrt,
			   chunkdata + chcpystrt,
			   (chcpyend - chcpystrt) + 1);

		nextidx++;
	}

	/*
	 * Final checks that we successfully fetched the datum
	 */
	if (nextidx != (endchunk + 1))
		elog(ERROR, "missing chunk number %d for toast value %u in %s",
			 nextidx,
			 toast_pointer.va_valueid,
			 RelationGetRelationName(toastrel));

	/*
	 * End scan and close relations
	 */
	systable_endscan_ordered(toastscan);
	toast_close_indexes(toastidxs, num_indexes, AccessShareLock);
	table_close(toastrel, AccessShareLock);

	return result;
}