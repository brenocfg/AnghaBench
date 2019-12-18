#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int int16 ;
struct TYPE_14__ {int /*<<< orphan*/  type_id; TYPE_1__* rngelemtype; } ;
typedef  TYPE_2__ TypeCacheEntry ;
struct TYPE_16__ {int lower; void* val; scalar_t__ inclusive; scalar_t__ infinite; } ;
struct TYPE_15__ {int /*<<< orphan*/  rangetypid; } ;
struct TYPE_13__ {int typlen; int typbyval; char typalign; char typstorage; } ;
typedef  int Size ;
typedef  TYPE_3__ RangeType ;
typedef  TYPE_4__ RangeBound ;
typedef  char* Pointer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_DATA_EXCEPTION ; 
 int /*<<< orphan*/  ERROR ; 
 int MAXALIGN (int) ; 
 int /*<<< orphan*/  PG_DETOAST_DATUM_PACKED (void*) ; 
 void* PointerGetDatum (int /*<<< orphan*/ ) ; 
 char RANGE_EMPTY ; 
 scalar_t__ RANGE_HAS_LBOUND (char) ; 
 scalar_t__ RANGE_HAS_UBOUND (char) ; 
 char RANGE_LB_INC ; 
 char RANGE_LB_INF ; 
 char RANGE_UB_INC ; 
 char RANGE_UB_INF ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_3__*,int) ; 
 int datum_compute_size (int,void*,int,char,int,char) ; 
 char* datum_write (char*,void*,int,char,int,char) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ palloc0 (int) ; 
 int range_cmp_bound_values (TYPE_2__*,TYPE_4__*,TYPE_4__*) ; 

RangeType *
range_serialize(TypeCacheEntry *typcache, RangeBound *lower, RangeBound *upper,
				bool empty)
{
	RangeType  *range;
	int			cmp;
	Size		msize;
	Pointer		ptr;
	int16		typlen;
	bool		typbyval;
	char		typalign;
	char		typstorage;
	char		flags = 0;

	/*
	 * Verify range is not invalid on its face, and construct flags value,
	 * preventing any non-canonical combinations such as infinite+inclusive.
	 */
	Assert(lower->lower);
	Assert(!upper->lower);

	if (empty)
		flags |= RANGE_EMPTY;
	else
	{
		cmp = range_cmp_bound_values(typcache, lower, upper);

		/* error check: if lower bound value is above upper, it's wrong */
		if (cmp > 0)
			ereport(ERROR,
					(errcode(ERRCODE_DATA_EXCEPTION),
					 errmsg("range lower bound must be less than or equal to range upper bound")));

		/* if bounds are equal, and not both inclusive, range is empty */
		if (cmp == 0 && !(lower->inclusive && upper->inclusive))
			flags |= RANGE_EMPTY;
		else
		{
			/* infinite boundaries are never inclusive */
			if (lower->infinite)
				flags |= RANGE_LB_INF;
			else if (lower->inclusive)
				flags |= RANGE_LB_INC;
			if (upper->infinite)
				flags |= RANGE_UB_INF;
			else if (upper->inclusive)
				flags |= RANGE_UB_INC;
		}
	}

	/* Fetch information about range's element type */
	typlen = typcache->rngelemtype->typlen;
	typbyval = typcache->rngelemtype->typbyval;
	typalign = typcache->rngelemtype->typalign;
	typstorage = typcache->rngelemtype->typstorage;

	/* Count space for varlena header and range type's OID */
	msize = sizeof(RangeType);
	Assert(msize == MAXALIGN(msize));

	/* Count space for bounds */
	if (RANGE_HAS_LBOUND(flags))
	{
		/*
		 * Make sure item to be inserted is not toasted.  It is essential that
		 * we not insert an out-of-line toast value pointer into a range
		 * object, for the same reasons that arrays and records can't contain
		 * them.  It would work to store a compressed-in-line value, but we
		 * prefer to decompress and then let compression be applied to the
		 * whole range object if necessary.  But, unlike arrays, we do allow
		 * short-header varlena objects to stay as-is.
		 */
		if (typlen == -1)
			lower->val = PointerGetDatum(PG_DETOAST_DATUM_PACKED(lower->val));

		msize = datum_compute_size(msize, lower->val, typbyval, typalign,
								   typlen, typstorage);
	}

	if (RANGE_HAS_UBOUND(flags))
	{
		/* Make sure item to be inserted is not toasted */
		if (typlen == -1)
			upper->val = PointerGetDatum(PG_DETOAST_DATUM_PACKED(upper->val));

		msize = datum_compute_size(msize, upper->val, typbyval, typalign,
								   typlen, typstorage);
	}

	/* Add space for flag byte */
	msize += sizeof(char);

	/* Note: zero-fill is required here, just as in heap tuples */
	range = (RangeType *) palloc0(msize);
	SET_VARSIZE(range, msize);

	/* Now fill in the datum */
	range->rangetypid = typcache->type_id;

	ptr = (char *) (range + 1);

	if (RANGE_HAS_LBOUND(flags))
	{
		Assert(lower->lower);
		ptr = datum_write(ptr, lower->val, typbyval, typalign, typlen,
						  typstorage);
	}

	if (RANGE_HAS_UBOUND(flags))
	{
		Assert(!upper->lower);
		ptr = datum_write(ptr, upper->val, typbyval, typalign, typlen,
						  typstorage);
	}

	*((char *) ptr) = flags;

	return range;
}