#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct varlena {int dummy; } ;
typedef  scalar_t__ int32 ;
struct TYPE_3__ {scalar_t__ min_input_size; scalar_t__ max_input_size; } ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ PGLZ_MAX_OUTPUT (scalar_t__) ; 
 TYPE_1__* PGLZ_strategy_default ; 
 int /*<<< orphan*/  PointerGetDatum (struct varlena*) ; 
 int /*<<< orphan*/  SET_VARSIZE_COMPRESSED (struct varlena*,scalar_t__) ; 
 scalar_t__ TOAST_COMPRESS_HDRSZ ; 
 int /*<<< orphan*/  TOAST_COMPRESS_RAWDATA (struct varlena*) ; 
 int /*<<< orphan*/  TOAST_COMPRESS_SET_RAWSIZE (struct varlena*,scalar_t__) ; 
 int /*<<< orphan*/  VARATT_IS_COMPRESSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARATT_IS_EXTERNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARDATA_ANY (int /*<<< orphan*/ ) ; 
 scalar_t__ VARSIZE_ANY_EXHDR (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (scalar_t__) ; 
 int /*<<< orphan*/  pfree (struct varlena*) ; 
 scalar_t__ pglz_compress (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 

Datum
toast_compress_datum(Datum value)
{
	struct varlena *tmp;
	int32		valsize = VARSIZE_ANY_EXHDR(DatumGetPointer(value));
	int32		len;

	Assert(!VARATT_IS_EXTERNAL(DatumGetPointer(value)));
	Assert(!VARATT_IS_COMPRESSED(DatumGetPointer(value)));

	/*
	 * No point in wasting a palloc cycle if value size is out of the allowed
	 * range for compression
	 */
	if (valsize < PGLZ_strategy_default->min_input_size ||
		valsize > PGLZ_strategy_default->max_input_size)
		return PointerGetDatum(NULL);

	tmp = (struct varlena *) palloc(PGLZ_MAX_OUTPUT(valsize) +
									TOAST_COMPRESS_HDRSZ);

	/*
	 * We recheck the actual size even if pglz_compress() reports success,
	 * because it might be satisfied with having saved as little as one byte
	 * in the compressed data --- which could turn into a net loss once you
	 * consider header and alignment padding.  Worst case, the compressed
	 * format might require three padding bytes (plus header, which is
	 * included in VARSIZE(tmp)), whereas the uncompressed format would take
	 * only one header byte and no padding if the value is short enough.  So
	 * we insist on a savings of more than 2 bytes to ensure we have a gain.
	 */
	len = pglz_compress(VARDATA_ANY(DatumGetPointer(value)),
						valsize,
						TOAST_COMPRESS_RAWDATA(tmp),
						PGLZ_strategy_default);
	if (len >= 0 &&
		len + TOAST_COMPRESS_HDRSZ < valsize - 2)
	{
		TOAST_COMPRESS_SET_RAWSIZE(tmp, valsize);
		SET_VARSIZE_COMPRESSED(tmp, len + TOAST_COMPRESS_HDRSZ);
		/* successful compression */
		return PointerGetDatum(tmp);
	}
	else
	{
		/* incompressible data */
		pfree(tmp);
		return PointerGetDatum(NULL);
	}
}