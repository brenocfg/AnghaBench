#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int strlen (char*) ; 

__attribute__((used)) static double
convert_one_string_to_scalar(char *value, int rangelo, int rangehi)
{
	int			slen = strlen(value);
	double		num,
				denom,
				base;

	if (slen <= 0)
		return 0.0;				/* empty string has scalar value 0 */

	/*
	 * There seems little point in considering more than a dozen bytes from
	 * the string.  Since base is at least 10, that will give us nominal
	 * resolution of at least 12 decimal digits, which is surely far more
	 * precision than this estimation technique has got anyway (especially in
	 * non-C locales).  Also, even with the maximum possible base of 256, this
	 * ensures denom cannot grow larger than 256^13 = 2.03e31, which will not
	 * overflow on any known machine.
	 */
	if (slen > 12)
		slen = 12;

	/* Convert initial characters to fraction */
	base = rangehi - rangelo + 1;
	num = 0.0;
	denom = base;
	while (slen-- > 0)
	{
		int			ch = (unsigned char) *value++;

		if (ch < rangelo)
			ch = rangelo - 1;
		else if (ch > rangehi)
			ch = rangehi + 1;
		num += ((double) (ch - rangelo)) / denom;
		denom *= base;
	}

	return num;
}