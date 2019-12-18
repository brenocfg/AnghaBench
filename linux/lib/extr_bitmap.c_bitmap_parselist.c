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
struct region {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char const*) ; 
 int PTR_ERR (char const*) ; 
 long bitmap_check_region (struct region*) ; 
 char* bitmap_find_region (char const*) ; 
 char* bitmap_parse_region (char const*,struct region*) ; 
 long bitmap_set_region (struct region*,unsigned long*,int) ; 
 int /*<<< orphan*/  bitmap_zero (unsigned long*,int) ; 

int bitmap_parselist(const char *buf, unsigned long *maskp, int nmaskbits)
{
	struct region r;
	long ret;

	bitmap_zero(maskp, nmaskbits);

	while (buf) {
		buf = bitmap_find_region(buf);
		if (buf == NULL)
			return 0;

		buf = bitmap_parse_region(buf, &r);
		if (IS_ERR(buf))
			return PTR_ERR(buf);

		ret = bitmap_check_region(&r);
		if (ret)
			return ret;

		ret = bitmap_set_region(&r, maskp, nmaskbits);
		if (ret)
			return ret;
	}

	return 0;
}