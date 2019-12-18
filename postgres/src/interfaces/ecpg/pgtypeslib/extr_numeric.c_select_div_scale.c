#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ndigits; scalar_t__* digits; int weight; int /*<<< orphan*/  dscale; } ;
typedef  TYPE_1__ numeric ;
typedef  scalar_t__ NumericDigit ;

/* Variables and functions */
 int Max (int,int /*<<< orphan*/ ) ; 
 int Min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMERIC_MAX_DISPLAY_SCALE ; 
 int /*<<< orphan*/  NUMERIC_MIN_DISPLAY_SCALE ; 
 int NUMERIC_MIN_SIG_DIGITS ; 

__attribute__((used)) static int
select_div_scale(numeric *var1, numeric *var2, int *rscale)
{
	int			weight1,
				weight2,
				qweight,
				i;
	NumericDigit firstdigit1,
				firstdigit2;
	int			res_dscale;

	/*
	 * The result scale of a division isn't specified in any SQL standard. For
	 * PostgreSQL we select a display scale that will give at least
	 * NUMERIC_MIN_SIG_DIGITS significant digits, so that numeric gives a
	 * result no less accurate than float8; but use a scale not less than
	 * either input's display scale.
	 */

	/* Get the actual (normalized) weight and first digit of each input */

	weight1 = 0;				/* values to use if var1 is zero */
	firstdigit1 = 0;
	for (i = 0; i < var1->ndigits; i++)
	{
		firstdigit1 = var1->digits[i];
		if (firstdigit1 != 0)
		{
			weight1 = var1->weight - i;
			break;
		}
	}

	weight2 = 0;				/* values to use if var2 is zero */
	firstdigit2 = 0;
	for (i = 0; i < var2->ndigits; i++)
	{
		firstdigit2 = var2->digits[i];
		if (firstdigit2 != 0)
		{
			weight2 = var2->weight - i;
			break;
		}
	}

	/*
	 * Estimate weight of quotient.  If the two first digits are equal, we
	 * can't be sure, but assume that var1 is less than var2.
	 */
	qweight = weight1 - weight2;
	if (firstdigit1 <= firstdigit2)
		qweight--;

	/* Select display scale */
	res_dscale = NUMERIC_MIN_SIG_DIGITS - qweight;
	res_dscale = Max(res_dscale, var1->dscale);
	res_dscale = Max(res_dscale, var2->dscale);
	res_dscale = Max(res_dscale, NUMERIC_MIN_DISPLAY_SCALE);
	res_dscale = Min(res_dscale, NUMERIC_MAX_DISPLAY_SCALE);

	/* Select result scale */
	*rscale = res_dscale + 4;

	return res_dscale;
}