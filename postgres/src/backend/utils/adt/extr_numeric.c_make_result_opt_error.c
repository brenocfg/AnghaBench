#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int n_sign_dscale; int n_weight; } ;
struct TYPE_14__ {int n_header; } ;
struct TYPE_16__ {int n_header; TYPE_2__ n_long; TYPE_1__ n_short; } ;
struct TYPE_18__ {TYPE_3__ choice; } ;
struct TYPE_17__ {int weight; int sign; int ndigits; int dscale; scalar_t__* digits; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_4__ NumericVar ;
typedef  scalar_t__ NumericDigit ;
typedef  TYPE_5__* Numeric ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ NUMERIC_CAN_BE_SHORT (int,int) ; 
 int /*<<< orphan*/  NUMERIC_DIGITS (TYPE_5__*) ; 
 int NUMERIC_DSCALE (TYPE_5__*) ; 
 int NUMERIC_DSCALE_MASK ; 
 scalar_t__ NUMERIC_HDRSZ ; 
 scalar_t__ NUMERIC_HDRSZ_SHORT ; 
 int NUMERIC_NAN ; 
 int NUMERIC_NDIGITS (TYPE_5__*) ; 
 int NUMERIC_NEG ; 
 int NUMERIC_POS ; 
 int NUMERIC_SHORT ; 
 int NUMERIC_SHORT_DSCALE_SHIFT ; 
 int NUMERIC_SHORT_SIGN_MASK ; 
 int NUMERIC_SHORT_WEIGHT_MASK ; 
 int NUMERIC_SHORT_WEIGHT_SIGN_MASK ; 
 int NUMERIC_WEIGHT (TYPE_5__*) ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  dump_numeric (char*,TYPE_5__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ palloc (scalar_t__) ; 

__attribute__((used)) static Numeric
make_result_opt_error(const NumericVar *var, bool *have_error)
{
	Numeric		result;
	NumericDigit *digits = var->digits;
	int			weight = var->weight;
	int			sign = var->sign;
	int			n;
	Size		len;

	if (have_error)
		*have_error = false;

	if (sign == NUMERIC_NAN)
	{
		result = (Numeric) palloc(NUMERIC_HDRSZ_SHORT);

		SET_VARSIZE(result, NUMERIC_HDRSZ_SHORT);
		result->choice.n_header = NUMERIC_NAN;
		/* the header word is all we need */

		dump_numeric("make_result()", result);
		return result;
	}

	n = var->ndigits;

	/* truncate leading zeroes */
	while (n > 0 && *digits == 0)
	{
		digits++;
		weight--;
		n--;
	}
	/* truncate trailing zeroes */
	while (n > 0 && digits[n - 1] == 0)
		n--;

	/* If zero result, force to weight=0 and positive sign */
	if (n == 0)
	{
		weight = 0;
		sign = NUMERIC_POS;
	}

	/* Build the result */
	if (NUMERIC_CAN_BE_SHORT(var->dscale, weight))
	{
		len = NUMERIC_HDRSZ_SHORT + n * sizeof(NumericDigit);
		result = (Numeric) palloc(len);
		SET_VARSIZE(result, len);
		result->choice.n_short.n_header =
			(sign == NUMERIC_NEG ? (NUMERIC_SHORT | NUMERIC_SHORT_SIGN_MASK)
			 : NUMERIC_SHORT)
			| (var->dscale << NUMERIC_SHORT_DSCALE_SHIFT)
			| (weight < 0 ? NUMERIC_SHORT_WEIGHT_SIGN_MASK : 0)
			| (weight & NUMERIC_SHORT_WEIGHT_MASK);
	}
	else
	{
		len = NUMERIC_HDRSZ + n * sizeof(NumericDigit);
		result = (Numeric) palloc(len);
		SET_VARSIZE(result, len);
		result->choice.n_long.n_sign_dscale =
			sign | (var->dscale & NUMERIC_DSCALE_MASK);
		result->choice.n_long.n_weight = weight;
	}

	Assert(NUMERIC_NDIGITS(result) == n);
	if (n > 0)
		memcpy(NUMERIC_DIGITS(result), digits, n * sizeof(NumericDigit));

	/* Check for overflow of int16 fields */
	if (NUMERIC_WEIGHT(result) != weight ||
		NUMERIC_DSCALE(result) != var->dscale)
	{
		if (have_error)
		{
			*have_error = true;
			return NULL;
		}
		else
		{
			ereport(ERROR,
					(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
					 errmsg("value overflows numeric format")));
		}
	}

	dump_numeric("make_result()", result);
	return result;
}