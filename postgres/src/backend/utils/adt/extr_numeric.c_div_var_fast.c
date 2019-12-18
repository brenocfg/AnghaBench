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
struct TYPE_10__ {int ndigits; int* digits; int dscale; scalar_t__ sign; int weight; } ;
typedef  TYPE_1__ NumericVar ;
typedef  int NumericDigit ;

/* Variables and functions */
 scalar_t__ Abs (int) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int DEC_DIGITS ; 
 int DIV_GUARD_DIGITS ; 
 int /*<<< orphan*/  ERRCODE_DIVISION_BY_ZERO ; 
 int /*<<< orphan*/  ERROR ; 
 double INT_MAX ; 
 int Min (int,int) ; 
 double NBASE ; 
 int NUMERIC_NEG ; 
 int NUMERIC_POS ; 
 int /*<<< orphan*/  alloc_var (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pfree (int*) ; 
 int /*<<< orphan*/  round_var (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strip_var (TYPE_1__*) ; 
 int /*<<< orphan*/  trunc_var (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zero_var (TYPE_1__*) ; 

__attribute__((used)) static void
div_var_fast(const NumericVar *var1, const NumericVar *var2,
			 NumericVar *result, int rscale, bool round)
{
	int			div_ndigits;
	int			res_sign;
	int			res_weight;
	int		   *div;
	int			qdigit;
	int			carry;
	int			maxdiv;
	int			newdig;
	NumericDigit *res_digits;
	double		fdividend,
				fdivisor,
				fdivisorinverse,
				fquotient;
	int			qi;
	int			i;

	/* copy these values into local vars for speed in inner loop */
	int			var1ndigits = var1->ndigits;
	int			var2ndigits = var2->ndigits;
	NumericDigit *var1digits = var1->digits;
	NumericDigit *var2digits = var2->digits;

	/*
	 * First of all division by zero check; we must not be handed an
	 * unnormalized divisor.
	 */
	if (var2ndigits == 0 || var2digits[0] == 0)
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
	 * Determine the result sign, weight and number of digits to calculate
	 */
	if (var1->sign == var2->sign)
		res_sign = NUMERIC_POS;
	else
		res_sign = NUMERIC_NEG;
	res_weight = var1->weight - var2->weight + 1;
	/* The number of accurate result digits we need to produce: */
	div_ndigits = res_weight + 1 + (rscale + DEC_DIGITS - 1) / DEC_DIGITS;
	/* Add guard digits for roundoff error */
	div_ndigits += DIV_GUARD_DIGITS;
	if (div_ndigits < DIV_GUARD_DIGITS)
		div_ndigits = DIV_GUARD_DIGITS;
	/* Must be at least var1ndigits, too, to simplify data-loading loop */
	if (div_ndigits < var1ndigits)
		div_ndigits = var1ndigits;

	/*
	 * We do the arithmetic in an array "div[]" of signed int's.  Since
	 * INT_MAX is noticeably larger than NBASE*NBASE, this gives us headroom
	 * to avoid normalizing carries immediately.
	 *
	 * We start with div[] containing one zero digit followed by the
	 * dividend's digits (plus appended zeroes to reach the desired precision
	 * including guard digits).  Each step of the main loop computes an
	 * (approximate) quotient digit and stores it into div[], removing one
	 * position of dividend space.  A final pass of carry propagation takes
	 * care of any mistaken quotient digits.
	 */
	div = (int *) palloc0((div_ndigits + 1) * sizeof(int));
	for (i = 0; i < var1ndigits; i++)
		div[i + 1] = var1digits[i];

	/*
	 * We estimate each quotient digit using floating-point arithmetic, taking
	 * the first four digits of the (current) dividend and divisor.  This must
	 * be float to avoid overflow.  The quotient digits will generally be off
	 * by no more than one from the exact answer.
	 */
	fdivisor = (double) var2digits[0];
	for (i = 1; i < 4; i++)
	{
		fdivisor *= NBASE;
		if (i < var2ndigits)
			fdivisor += (double) var2digits[i];
	}
	fdivisorinverse = 1.0 / fdivisor;

	/*
	 * maxdiv tracks the maximum possible absolute value of any div[] entry;
	 * when this threatens to exceed INT_MAX, we take the time to propagate
	 * carries.  Furthermore, we need to ensure that overflow doesn't occur
	 * during the carry propagation passes either.  The carry values may have
	 * an absolute value as high as INT_MAX/NBASE + 1, so really we must
	 * normalize when digits threaten to exceed INT_MAX - INT_MAX/NBASE - 1.
	 *
	 * To avoid overflow in maxdiv itself, it represents the max absolute
	 * value divided by NBASE-1, ie, at the top of the loop it is known that
	 * no div[] entry has an absolute value exceeding maxdiv * (NBASE-1).
	 *
	 * Actually, though, that holds good only for div[] entries after div[qi];
	 * the adjustment done at the bottom of the loop may cause div[qi + 1] to
	 * exceed the maxdiv limit, so that div[qi] in the next iteration is
	 * beyond the limit.  This does not cause problems, as explained below.
	 */
	maxdiv = 1;

	/*
	 * Outer loop computes next quotient digit, which will go into div[qi]
	 */
	for (qi = 0; qi < div_ndigits; qi++)
	{
		/* Approximate the current dividend value */
		fdividend = (double) div[qi];
		for (i = 1; i < 4; i++)
		{
			fdividend *= NBASE;
			if (qi + i <= div_ndigits)
				fdividend += (double) div[qi + i];
		}
		/* Compute the (approximate) quotient digit */
		fquotient = fdividend * fdivisorinverse;
		qdigit = (fquotient >= 0.0) ? ((int) fquotient) :
			(((int) fquotient) - 1);	/* truncate towards -infinity */

		if (qdigit != 0)
		{
			/* Do we need to normalize now? */
			maxdiv += Abs(qdigit);
			if (maxdiv > (INT_MAX - INT_MAX / NBASE - 1) / (NBASE - 1))
			{
				/* Yes, do it */
				carry = 0;
				for (i = div_ndigits; i > qi; i--)
				{
					newdig = div[i] + carry;
					if (newdig < 0)
					{
						carry = -((-newdig - 1) / NBASE) - 1;
						newdig -= carry * NBASE;
					}
					else if (newdig >= NBASE)
					{
						carry = newdig / NBASE;
						newdig -= carry * NBASE;
					}
					else
						carry = 0;
					div[i] = newdig;
				}
				newdig = div[qi] + carry;
				div[qi] = newdig;

				/*
				 * All the div[] digits except possibly div[qi] are now in the
				 * range 0..NBASE-1.  We do not need to consider div[qi] in
				 * the maxdiv value anymore, so we can reset maxdiv to 1.
				 */
				maxdiv = 1;

				/*
				 * Recompute the quotient digit since new info may have
				 * propagated into the top four dividend digits
				 */
				fdividend = (double) div[qi];
				for (i = 1; i < 4; i++)
				{
					fdividend *= NBASE;
					if (qi + i <= div_ndigits)
						fdividend += (double) div[qi + i];
				}
				/* Compute the (approximate) quotient digit */
				fquotient = fdividend * fdivisorinverse;
				qdigit = (fquotient >= 0.0) ? ((int) fquotient) :
					(((int) fquotient) - 1);	/* truncate towards -infinity */
				maxdiv += Abs(qdigit);
			}

			/*
			 * Subtract off the appropriate multiple of the divisor.
			 *
			 * The digits beyond div[qi] cannot overflow, because we know they
			 * will fall within the maxdiv limit.  As for div[qi] itself, note
			 * that qdigit is approximately trunc(div[qi] / vardigits[0]),
			 * which would make the new value simply div[qi] mod vardigits[0].
			 * The lower-order terms in qdigit can change this result by not
			 * more than about twice INT_MAX/NBASE, so overflow is impossible.
			 */
			if (qdigit != 0)
			{
				int			istop = Min(var2ndigits, div_ndigits - qi + 1);

				for (i = 0; i < istop; i++)
					div[qi + i] -= qdigit * var2digits[i];
			}
		}

		/*
		 * The dividend digit we are about to replace might still be nonzero.
		 * Fold it into the next digit position.
		 *
		 * There is no risk of overflow here, although proving that requires
		 * some care.  Much as with the argument for div[qi] not overflowing,
		 * if we consider the first two terms in the numerator and denominator
		 * of qdigit, we can see that the final value of div[qi + 1] will be
		 * approximately a remainder mod (vardigits[0]*NBASE + vardigits[1]).
		 * Accounting for the lower-order terms is a bit complicated but ends
		 * up adding not much more than INT_MAX/NBASE to the possible range.
		 * Thus, div[qi + 1] cannot overflow here, and in its role as div[qi]
		 * in the next loop iteration, it can't be large enough to cause
		 * overflow in the carry propagation step (if any), either.
		 *
		 * But having said that: div[qi] can be more than INT_MAX/NBASE, as
		 * noted above, which means that the product div[qi] * NBASE *can*
		 * overflow.  When that happens, adding it to div[qi + 1] will always
		 * cause a canceling overflow so that the end result is correct.  We
		 * could avoid the intermediate overflow by doing the multiplication
		 * and addition in int64 arithmetic, but so far there appears no need.
		 */
		div[qi + 1] += div[qi] * NBASE;

		div[qi] = qdigit;
	}

	/*
	 * Approximate and store the last quotient digit (div[div_ndigits])
	 */
	fdividend = (double) div[qi];
	for (i = 1; i < 4; i++)
		fdividend *= NBASE;
	fquotient = fdividend * fdivisorinverse;
	qdigit = (fquotient >= 0.0) ? ((int) fquotient) :
		(((int) fquotient) - 1);	/* truncate towards -infinity */
	div[qi] = qdigit;

	/*
	 * Because the quotient digits might be off by one, some of them might be
	 * -1 or NBASE at this point.  The represented value is correct in a
	 * mathematical sense, but it doesn't look right.  We do a final carry
	 * propagation pass to normalize the digits, which we combine with storing
	 * the result digits into the output.  Note that this is still done at
	 * full precision w/guard digits.
	 */
	alloc_var(result, div_ndigits + 1);
	res_digits = result->digits;
	carry = 0;
	for (i = div_ndigits; i >= 0; i--)
	{
		newdig = div[i] + carry;
		if (newdig < 0)
		{
			carry = -((-newdig - 1) / NBASE) - 1;
			newdig -= carry * NBASE;
		}
		else if (newdig >= NBASE)
		{
			carry = newdig / NBASE;
			newdig -= carry * NBASE;
		}
		else
			carry = 0;
		res_digits[i] = newdig;
	}
	Assert(carry == 0);

	pfree(div);

	/*
	 * Finally, round the result to the requested precision.
	 */
	result->weight = res_weight;
	result->sign = res_sign;

	/* Round to target rscale (and set result->dscale) */
	if (round)
		round_var(result, rscale);
	else
		trunc_var(result, rscale);

	/* Strip leading and trailing zeroes */
	strip_var(result);
}