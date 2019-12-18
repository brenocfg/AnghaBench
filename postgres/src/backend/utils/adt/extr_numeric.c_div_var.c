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
struct TYPE_10__ {int ndigits; scalar_t__* digits; int dscale; scalar_t__ sign; int weight; } ;
typedef  TYPE_1__ NumericVar ;
typedef  int NumericDigit ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int DEC_DIGITS ; 
 int /*<<< orphan*/  ERRCODE_DIVISION_BY_ZERO ; 
 int /*<<< orphan*/  ERROR ; 
 int HALF_NBASE ; 
 int Max (int,int) ; 
 int NBASE ; 
 int NUMERIC_NEG ; 
 int NUMERIC_POS ; 
 int /*<<< orphan*/  alloc_var (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  memcpy (int*,scalar_t__*,int) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pfree (int*) ; 
 int /*<<< orphan*/  round_var (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strip_var (TYPE_1__*) ; 
 int /*<<< orphan*/  trunc_var (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zero_var (TYPE_1__*) ; 

__attribute__((used)) static void
div_var(const NumericVar *var1, const NumericVar *var2, NumericVar *result,
		int rscale, bool round)
{
	int			div_ndigits;
	int			res_ndigits;
	int			res_sign;
	int			res_weight;
	int			carry;
	int			borrow;
	int			divisor1;
	int			divisor2;
	NumericDigit *dividend;
	NumericDigit *divisor;
	NumericDigit *res_digits;
	int			i;
	int			j;

	/* copy these values into local vars for speed in inner loop */
	int			var1ndigits = var1->ndigits;
	int			var2ndigits = var2->ndigits;

	/*
	 * First of all division by zero check; we must not be handed an
	 * unnormalized divisor.
	 */
	if (var2ndigits == 0 || var2->digits[0] == 0)
		ereport(ERROR,
				(errcode(ERRCODE_DIVISION_BY_ZERO),
				 errmsg("division by zero")));

	/*
	 * Now result zero check
	 */
	if (var1ndigits == 0)
	{
		zero_var(result);
		result->dscale = rscale;
		return;
	}

	/*
	 * Determine the result sign, weight and number of digits to calculate.
	 * The weight figured here is correct if the emitted quotient has no
	 * leading zero digits; otherwise strip_var() will fix things up.
	 */
	if (var1->sign == var2->sign)
		res_sign = NUMERIC_POS;
	else
		res_sign = NUMERIC_NEG;
	res_weight = var1->weight - var2->weight;
	/* The number of accurate result digits we need to produce: */
	res_ndigits = res_weight + 1 + (rscale + DEC_DIGITS - 1) / DEC_DIGITS;
	/* ... but always at least 1 */
	res_ndigits = Max(res_ndigits, 1);
	/* If rounding needed, figure one more digit to ensure correct result */
	if (round)
		res_ndigits++;

	/*
	 * The working dividend normally requires res_ndigits + var2ndigits
	 * digits, but make it at least var1ndigits so we can load all of var1
	 * into it.  (There will be an additional digit dividend[0] in the
	 * dividend space, but for consistency with Knuth's notation we don't
	 * count that in div_ndigits.)
	 */
	div_ndigits = res_ndigits + var2ndigits;
	div_ndigits = Max(div_ndigits, var1ndigits);

	/*
	 * We need a workspace with room for the working dividend (div_ndigits+1
	 * digits) plus room for the possibly-normalized divisor (var2ndigits
	 * digits).  It is convenient also to have a zero at divisor[0] with the
	 * actual divisor data in divisor[1 .. var2ndigits].  Transferring the
	 * digits into the workspace also allows us to realloc the result (which
	 * might be the same as either input var) before we begin the main loop.
	 * Note that we use palloc0 to ensure that divisor[0], dividend[0], and
	 * any additional dividend positions beyond var1ndigits, start out 0.
	 */
	dividend = (NumericDigit *)
		palloc0((div_ndigits + var2ndigits + 2) * sizeof(NumericDigit));
	divisor = dividend + (div_ndigits + 1);
	memcpy(dividend + 1, var1->digits, var1ndigits * sizeof(NumericDigit));
	memcpy(divisor + 1, var2->digits, var2ndigits * sizeof(NumericDigit));

	/*
	 * Now we can realloc the result to hold the generated quotient digits.
	 */
	alloc_var(result, res_ndigits);
	res_digits = result->digits;

	if (var2ndigits == 1)
	{
		/*
		 * If there's only a single divisor digit, we can use a fast path (cf.
		 * Knuth section 4.3.1 exercise 16).
		 */
		divisor1 = divisor[1];
		carry = 0;
		for (i = 0; i < res_ndigits; i++)
		{
			carry = carry * NBASE + dividend[i + 1];
			res_digits[i] = carry / divisor1;
			carry = carry % divisor1;
		}
	}
	else
	{
		/*
		 * The full multiple-place algorithm is taken from Knuth volume 2,
		 * Algorithm 4.3.1D.
		 *
		 * We need the first divisor digit to be >= NBASE/2.  If it isn't,
		 * make it so by scaling up both the divisor and dividend by the
		 * factor "d".  (The reason for allocating dividend[0] above is to
		 * leave room for possible carry here.)
		 */
		if (divisor[1] < HALF_NBASE)
		{
			int			d = NBASE / (divisor[1] + 1);

			carry = 0;
			for (i = var2ndigits; i > 0; i--)
			{
				carry += divisor[i] * d;
				divisor[i] = carry % NBASE;
				carry = carry / NBASE;
			}
			Assert(carry == 0);
			carry = 0;
			/* at this point only var1ndigits of dividend can be nonzero */
			for (i = var1ndigits; i >= 0; i--)
			{
				carry += dividend[i] * d;
				dividend[i] = carry % NBASE;
				carry = carry / NBASE;
			}
			Assert(carry == 0);
			Assert(divisor[1] >= HALF_NBASE);
		}
		/* First 2 divisor digits are used repeatedly in main loop */
		divisor1 = divisor[1];
		divisor2 = divisor[2];

		/*
		 * Begin the main loop.  Each iteration of this loop produces the j'th
		 * quotient digit by dividing dividend[j .. j + var2ndigits] by the
		 * divisor; this is essentially the same as the common manual
		 * procedure for long division.
		 */
		for (j = 0; j < res_ndigits; j++)
		{
			/* Estimate quotient digit from the first two dividend digits */
			int			next2digits = dividend[j] * NBASE + dividend[j + 1];
			int			qhat;

			/*
			 * If next2digits are 0, then quotient digit must be 0 and there's
			 * no need to adjust the working dividend.  It's worth testing
			 * here to fall out ASAP when processing trailing zeroes in a
			 * dividend.
			 */
			if (next2digits == 0)
			{
				res_digits[j] = 0;
				continue;
			}

			if (dividend[j] == divisor1)
				qhat = NBASE - 1;
			else
				qhat = next2digits / divisor1;

			/*
			 * Adjust quotient digit if it's too large.  Knuth proves that
			 * after this step, the quotient digit will be either correct or
			 * just one too large.  (Note: it's OK to use dividend[j+2] here
			 * because we know the divisor length is at least 2.)
			 */
			while (divisor2 * qhat >
				   (next2digits - qhat * divisor1) * NBASE + dividend[j + 2])
				qhat--;

			/* As above, need do nothing more when quotient digit is 0 */
			if (qhat > 0)
			{
				/*
				 * Multiply the divisor by qhat, and subtract that from the
				 * working dividend.  "carry" tracks the multiplication,
				 * "borrow" the subtraction (could we fold these together?)
				 */
				carry = 0;
				borrow = 0;
				for (i = var2ndigits; i >= 0; i--)
				{
					carry += divisor[i] * qhat;
					borrow -= carry % NBASE;
					carry = carry / NBASE;
					borrow += dividend[j + i];
					if (borrow < 0)
					{
						dividend[j + i] = borrow + NBASE;
						borrow = -1;
					}
					else
					{
						dividend[j + i] = borrow;
						borrow = 0;
					}
				}
				Assert(carry == 0);

				/*
				 * If we got a borrow out of the top dividend digit, then
				 * indeed qhat was one too large.  Fix it, and add back the
				 * divisor to correct the working dividend.  (Knuth proves
				 * that this will occur only about 3/NBASE of the time; hence,
				 * it's a good idea to test this code with small NBASE to be
				 * sure this section gets exercised.)
				 */
				if (borrow)
				{
					qhat--;
					carry = 0;
					for (i = var2ndigits; i >= 0; i--)
					{
						carry += dividend[j + i] + divisor[i];
						if (carry >= NBASE)
						{
							dividend[j + i] = carry - NBASE;
							carry = 1;
						}
						else
						{
							dividend[j + i] = carry;
							carry = 0;
						}
					}
					/* A carry should occur here to cancel the borrow above */
					Assert(carry == 1);
				}
			}

			/* And we're done with this quotient digit */
			res_digits[j] = qhat;
		}
	}

	pfree(dividend);

	/*
	 * Finally, round or truncate the result to the requested precision.
	 */
	result->weight = res_weight;
	result->sign = res_sign;

	/* Round or truncate to target rscale (and set result->dscale) */
	if (round)
		round_var(result, rscale);
	else
		trunc_var(result, rscale);

	/* Strip leading and trailing zeroes */
	strip_var(result);
}