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
typedef  int s64 ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST_ULL (int,int) ; 
 int EINVAL ; 
 int power_of_ten (unsigned int) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int*,int*,int*,int*) ; 

int cgroup_parse_float(const char *input, unsigned dec_shift, s64 *v)
{
	s64 whole, frac = 0;
	int fstart = 0, fend = 0, flen;

	if (!sscanf(input, "%lld.%n%lld%n", &whole, &fstart, &frac, &fend))
		return -EINVAL;
	if (frac < 0)
		return -EINVAL;

	flen = fend > fstart ? fend - fstart : 0;
	if (flen < dec_shift)
		frac *= power_of_ten(dec_shift - flen);
	else
		frac = DIV_ROUND_CLOSEST_ULL(frac, power_of_ten(flen - dec_shift));

	*v = whole * power_of_ten(dec_shift) + frac;
	return 0;
}