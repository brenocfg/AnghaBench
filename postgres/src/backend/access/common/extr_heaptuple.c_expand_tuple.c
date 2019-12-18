#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
typedef  char bits8 ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_26__ {int /*<<< orphan*/  am_value; scalar_t__ am_present; } ;
struct TYPE_25__ {int /*<<< orphan*/  attlen; int /*<<< orphan*/  attalign; } ;
struct TYPE_24__ {int t_len; TYPE_3__* t_data; int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_tableOid; } ;
struct TYPE_23__ {int t_hoff; int t_len; int /*<<< orphan*/  t_infomask; int /*<<< orphan*/  t_ctid; } ;
struct TYPE_22__ {int natts; int /*<<< orphan*/  tdtypmod; int /*<<< orphan*/  tdtypeid; TYPE_1__* constr; } ;
struct TYPE_21__ {TYPE_7__* missing; } ;
typedef  int Size ;
typedef  TYPE_3__* MinimalTuple ;
typedef  TYPE_3__* HeapTupleHeader ;
typedef  TYPE_5__* HeapTuple ;
typedef  TYPE_6__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_7__ AttrMissing ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BITMAPLEN (int) ; 
 int HEAPTUPLESIZE ; 
 int HeapTupleHasNulls (TYPE_5__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderData ; 
 int HeapTupleHeaderGetNatts (TYPE_3__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetDatumLength (TYPE_3__*,int) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetNatts (TYPE_3__*,int) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetTypMod (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetTypeId (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 int MAXALIGN (int) ; 
 int MINIMAL_TUPLE_OFFSET ; 
 int /*<<< orphan*/  MinimalTupleData ; 
 int SizeofMinimalTupleHeader ; 
 TYPE_6__* TupleDescAttr (TYPE_2__*,int) ; 
 int att_addlength_pointer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int att_align_datum (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_val (TYPE_6__*,char**,int*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  t_bits ; 

__attribute__((used)) static void
expand_tuple(HeapTuple *targetHeapTuple,
			 MinimalTuple *targetMinimalTuple,
			 HeapTuple sourceTuple,
			 TupleDesc tupleDesc)
{
	AttrMissing *attrmiss = NULL;
	int			attnum;
	int			firstmissingnum = 0;
	bool		hasNulls = HeapTupleHasNulls(sourceTuple);
	HeapTupleHeader targetTHeader;
	HeapTupleHeader sourceTHeader = sourceTuple->t_data;
	int			sourceNatts = HeapTupleHeaderGetNatts(sourceTHeader);
	int			natts = tupleDesc->natts;
	int			sourceNullLen;
	int			targetNullLen;
	Size		sourceDataLen = sourceTuple->t_len - sourceTHeader->t_hoff;
	Size		targetDataLen;
	Size		len;
	int			hoff;
	bits8	   *nullBits = NULL;
	int			bitMask = 0;
	char	   *targetData;
	uint16	   *infoMask;

	Assert((targetHeapTuple && !targetMinimalTuple)
		   || (!targetHeapTuple && targetMinimalTuple));

	Assert(sourceNatts < natts);

	sourceNullLen = (hasNulls ? BITMAPLEN(sourceNatts) : 0);

	targetDataLen = sourceDataLen;

	if (tupleDesc->constr &&
		tupleDesc->constr->missing)
	{
		/*
		 * If there are missing values we want to put them into the tuple.
		 * Before that we have to compute the extra length for the values
		 * array and the variable length data.
		 */
		attrmiss = tupleDesc->constr->missing;

		/*
		 * Find the first item in attrmiss for which we don't have a value in
		 * the source. We can ignore all the missing entries before that.
		 */
		for (firstmissingnum = sourceNatts;
			 firstmissingnum < natts;
			 firstmissingnum++)
		{
			if (attrmiss[firstmissingnum].am_present)
				break;
			else
				hasNulls = true;
		}

		/*
		 * Now walk the missing attributes. If there is a missing value make
		 * space for it. Otherwise, it's going to be NULL.
		 */
		for (attnum = firstmissingnum;
			 attnum < natts;
			 attnum++)
		{
			if (attrmiss[attnum].am_present)
			{
				Form_pg_attribute att = TupleDescAttr(tupleDesc, attnum);

				targetDataLen = att_align_datum(targetDataLen,
												att->attalign,
												att->attlen,
												attrmiss[attnum].am_value);

				targetDataLen = att_addlength_pointer(targetDataLen,
													  att->attlen,
													  attrmiss[attnum].am_value);
			}
			else
			{
				/* no missing value, so it must be null */
				hasNulls = true;
			}
		}
	}							/* end if have missing values */
	else
	{
		/*
		 * If there are no missing values at all then NULLS must be allowed,
		 * since some of the attributes are known to be absent.
		 */
		hasNulls = true;
	}

	len = 0;

	if (hasNulls)
	{
		targetNullLen = BITMAPLEN(natts);
		len += targetNullLen;
	}
	else
		targetNullLen = 0;

	/*
	 * Allocate and zero the space needed.  Note that the tuple body and
	 * HeapTupleData management structure are allocated in one chunk.
	 */
	if (targetHeapTuple)
	{
		len += offsetof(HeapTupleHeaderData, t_bits);
		hoff = len = MAXALIGN(len); /* align user data safely */
		len += targetDataLen;

		*targetHeapTuple = (HeapTuple) palloc0(HEAPTUPLESIZE + len);
		(*targetHeapTuple)->t_data
			= targetTHeader
			= (HeapTupleHeader) ((char *) *targetHeapTuple + HEAPTUPLESIZE);
		(*targetHeapTuple)->t_len = len;
		(*targetHeapTuple)->t_tableOid = sourceTuple->t_tableOid;
		(*targetHeapTuple)->t_self = sourceTuple->t_self;

		targetTHeader->t_infomask = sourceTHeader->t_infomask;
		targetTHeader->t_hoff = hoff;
		HeapTupleHeaderSetNatts(targetTHeader, natts);
		HeapTupleHeaderSetDatumLength(targetTHeader, len);
		HeapTupleHeaderSetTypeId(targetTHeader, tupleDesc->tdtypeid);
		HeapTupleHeaderSetTypMod(targetTHeader, tupleDesc->tdtypmod);
		/* We also make sure that t_ctid is invalid unless explicitly set */
		ItemPointerSetInvalid(&(targetTHeader->t_ctid));
		if (targetNullLen > 0)
			nullBits = (bits8 *) ((char *) (*targetHeapTuple)->t_data
								  + offsetof(HeapTupleHeaderData, t_bits));
		targetData = (char *) (*targetHeapTuple)->t_data + hoff;
		infoMask = &(targetTHeader->t_infomask);
	}
	else
	{
		len += SizeofMinimalTupleHeader;
		hoff = len = MAXALIGN(len); /* align user data safely */
		len += targetDataLen;

		*targetMinimalTuple = (MinimalTuple) palloc0(len);
		(*targetMinimalTuple)->t_len = len;
		(*targetMinimalTuple)->t_hoff = hoff + MINIMAL_TUPLE_OFFSET;
		(*targetMinimalTuple)->t_infomask = sourceTHeader->t_infomask;
		/* Same macro works for MinimalTuples */
		HeapTupleHeaderSetNatts(*targetMinimalTuple, natts);
		if (targetNullLen > 0)
			nullBits = (bits8 *) ((char *) *targetMinimalTuple
								  + offsetof(MinimalTupleData, t_bits));
		targetData = (char *) *targetMinimalTuple + hoff;
		infoMask = &((*targetMinimalTuple)->t_infomask);
	}

	if (targetNullLen > 0)
	{
		if (sourceNullLen > 0)
		{
			/* if bitmap pre-existed copy in - all is set */
			memcpy(nullBits,
				   ((char *) sourceTHeader)
				   + offsetof(HeapTupleHeaderData, t_bits),
				   sourceNullLen);
			nullBits += sourceNullLen - 1;
		}
		else
		{
			sourceNullLen = BITMAPLEN(sourceNatts);
			/* Set NOT NULL for all existing attributes */
			memset(nullBits, 0xff, sourceNullLen);

			nullBits += sourceNullLen - 1;

			if (sourceNatts & 0x07)
			{
				/* build the mask (inverted!) */
				bitMask = 0xff << (sourceNatts & 0x07);
				/* Voila */
				*nullBits = ~bitMask;
			}
		}

		bitMask = (1 << ((sourceNatts - 1) & 0x07));
	}							/* End if have null bitmap */

	memcpy(targetData,
		   ((char *) sourceTuple->t_data) + sourceTHeader->t_hoff,
		   sourceDataLen);

	targetData += sourceDataLen;

	/* Now fill in the missing values */
	for (attnum = sourceNatts; attnum < natts; attnum++)
	{

		Form_pg_attribute attr = TupleDescAttr(tupleDesc, attnum);

		if (attrmiss && attrmiss[attnum].am_present)
		{
			fill_val(attr,
					 nullBits ? &nullBits : NULL,
					 &bitMask,
					 &targetData,
					 infoMask,
					 attrmiss[attnum].am_value,
					 false);
		}
		else
		{
			fill_val(attr,
					 &nullBits,
					 &bitMask,
					 &targetData,
					 infoMask,
					 (Datum) 0,
					 true);
		}
	}							/* end loop over missing attributes */
}