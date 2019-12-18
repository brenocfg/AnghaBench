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
 size_t tuklib_mbstr_width (char const*,size_t*) ; 

extern int
tuklib_mbstr_fw(const char *str, int columns_min)
{
	size_t len;
	const size_t width = tuklib_mbstr_width(str, &len);
	if (width == (size_t)-1)
		return -1;

	if (width > (size_t)columns_min)
		return 0;

	if (width < (size_t)columns_min)
		len += (size_t)columns_min - width;

	return len;
}