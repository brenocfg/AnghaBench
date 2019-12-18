#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ndigits; scalar_t__* digits; int weight; int rscale; int dscale; scalar_t__* buf; } ;
typedef  TYPE_1__ numeric ;
typedef  scalar_t__ NumericDigit ;

/* Variables and functions */
 int Max (int,int) ; 
 scalar_t__* digitbuf_alloc (int) ; 
 int /*<<< orphan*/  digitbuf_free (scalar_t__*) ; 

__attribute__((used)) static int
add_abs(numeric *var1, numeric *var2, numeric *result)
{
	NumericDigit *res_buf;
	NumericDigit *res_digits;
	int			res_ndigits;
	int			res_weight;
	int			res_rscale;
	int			res_dscale;
	int			i,
				i1,
				i2;
	int			carry = 0;

	/* copy these values into local vars for speed in inner loop */
	int			var1ndigits = var1->ndigits;
	int			var2ndigits = var2->ndigits;
	NumericDigit *var1digits = var1->digits;
	NumericDigit *var2digits = var2->digits;

	res_weight = Max(var1->weight, var2->weight) + 1;
	res_rscale = Max(var1->rscale, var2->rscale);
	res_dscale = Max(var1->dscale, var2->dscale);
	res_ndigits = res_rscale + res_weight + 1;
	if (res_ndigits <= 0)
		res_ndigits = 1;

	if ((res_buf = digitbuf_alloc(res_ndigits)) == NULL)
		return -1;
	res_digits = res_buf;

	i1 = res_rscale + var1->weight + 1;
	i2 = res_rscale + var2->weight + 1;
	for (i = res_ndigits - 1; i >= 0; i--)
	{
		i1--;
		i2--;
		if (i1 >= 0 && i1 < var1ndigits)
			carry += var1digits[i1];
		if (i2 >= 0 && i2 < var2ndigits)
			carry += var2digits[i2];

		if (carry >= 10)
		{
			res_digits[i] = carry - 10;
			carry = 1;
		}
		else
		{
			res_digits[i] = carry;
			carry = 0;
		}
	}

	while (res_ndigits > 0 && *res_digits == 0)
	{
		res_digits++;
		res_weight--;
		res_ndigits--;
	}
	while (res_ndigits > 0 && res_digits[res_ndigits - 1] == 0)
		res_ndigits--;

	if (res_ndigits == 0)
		res_weight = 0;

	digitbuf_free(result->buf);
	result->ndigits = res_ndigits;
	result->buf = res_buf;
	result->digits = res_digits;
	result->weight = res_weight;
	result->rscale = res_rscale;
	result->dscale = res_dscale;

	return 0;
}