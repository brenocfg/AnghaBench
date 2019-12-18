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
typedef  int int32 ;
struct TYPE_10__ {scalar_t__ ndigits; int weight; int /*<<< orphan*/ * digits; } ;
typedef  TYPE_1__ NumericVar ;

/* Variables and functions */
 int DEC_DIGITS ; 
 int /*<<< orphan*/  const_ten ; 
 int /*<<< orphan*/  div_var (TYPE_1__ const*,TYPE_1__*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  free_var (TYPE_1__*) ; 
 char* get_str_from_var (TYPE_1__*) ; 
 int /*<<< orphan*/  init_var (TYPE_1__*) ; 
 scalar_t__ log10 (int /*<<< orphan*/ ) ; 
 char* palloc (size_t) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  power_var_int (int /*<<< orphan*/ *,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
get_str_from_var_sci(const NumericVar *var, int rscale)
{
	int32		exponent;
	NumericVar	denominator;
	NumericVar	significand;
	int			denom_scale;
	size_t		len;
	char	   *str;
	char	   *sig_out;

	if (rscale < 0)
		rscale = 0;

	/*
	 * Determine the exponent of this number in normalised form.
	 *
	 * This is the exponent required to represent the number with only one
	 * significant digit before the decimal place.
	 */
	if (var->ndigits > 0)
	{
		exponent = (var->weight + 1) * DEC_DIGITS;

		/*
		 * Compensate for leading decimal zeroes in the first numeric digit by
		 * decrementing the exponent.
		 */
		exponent -= DEC_DIGITS - (int) log10(var->digits[0]);
	}
	else
	{
		/*
		 * If var has no digits, then it must be zero.
		 *
		 * Zero doesn't technically have a meaningful exponent in normalised
		 * notation, but we just display the exponent as zero for consistency
		 * of output.
		 */
		exponent = 0;
	}

	/*
	 * The denominator is set to 10 raised to the power of the exponent.
	 *
	 * We then divide var by the denominator to get the significand, rounding
	 * to rscale decimal digits in the process.
	 */
	if (exponent < 0)
		denom_scale = -exponent;
	else
		denom_scale = 0;

	init_var(&denominator);
	init_var(&significand);

	power_var_int(&const_ten, exponent, &denominator, denom_scale);
	div_var(var, &denominator, &significand, rscale, true);
	sig_out = get_str_from_var(&significand);

	free_var(&denominator);
	free_var(&significand);

	/*
	 * Allocate space for the result.
	 *
	 * In addition to the significand, we need room for the exponent
	 * decoration ("e"), the sign of the exponent, up to 10 digits for the
	 * exponent itself, and of course the null terminator.
	 */
	len = strlen(sig_out) + 13;
	str = palloc(len);
	snprintf(str, len, "%se%+03d", sig_out, exponent);

	pfree(sig_out);

	return str;
}