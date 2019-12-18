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
struct TYPE_5__ {int rscale; int weight; int ndigits; scalar_t__ sign; int* digits; int* buf; scalar_t__ dscale; } ;
typedef  TYPE_1__ numeric ;
typedef  int NumericDigit ;

/* Variables and functions */
 int NUMERIC_NEG ; 
 int NUMERIC_POS ; 
 int* digitbuf_alloc (int) ; 
 int /*<<< orphan*/  digitbuf_free (int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

int
PGTYPESnumeric_mul(numeric *var1, numeric *var2, numeric *result)
{
	NumericDigit *res_buf;
	NumericDigit *res_digits;
	int			res_ndigits;
	int			res_weight;
	int			res_sign;
	int			i,
				ri,
				i1,
				i2;
	long		sum = 0;
	int			global_rscale = var1->rscale + var2->rscale;

	res_weight = var1->weight + var2->weight + 2;
	res_ndigits = var1->ndigits + var2->ndigits + 1;
	if (var1->sign == var2->sign)
		res_sign = NUMERIC_POS;
	else
		res_sign = NUMERIC_NEG;

	if ((res_buf = digitbuf_alloc(res_ndigits)) == NULL)
		return -1;
	res_digits = res_buf;
	memset(res_digits, 0, res_ndigits);

	ri = res_ndigits;
	for (i1 = var1->ndigits - 1; i1 >= 0; i1--)
	{
		sum = 0;
		i = --ri;

		for (i2 = var2->ndigits - 1; i2 >= 0; i2--)
		{
			sum += res_digits[i] + var1->digits[i1] * var2->digits[i2];
			res_digits[i--] = sum % 10;
			sum /= 10;
		}
		res_digits[i] = sum;
	}

	i = res_weight + global_rscale + 2;
	if (i >= 0 && i < res_ndigits)
	{
		sum = (res_digits[i] > 4) ? 1 : 0;
		res_ndigits = i;
		i--;
		while (sum)
		{
			sum += res_digits[i];
			res_digits[i--] = sum % 10;
			sum /= 10;
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
	{
		res_sign = NUMERIC_POS;
		res_weight = 0;
	}

	digitbuf_free(result->buf);
	result->buf = res_buf;
	result->digits = res_digits;
	result->ndigits = res_ndigits;
	result->weight = res_weight;
	result->rscale = global_rscale;
	result->sign = res_sign;
	result->dscale = var1->dscale + var2->dscale;

	return 0;
}