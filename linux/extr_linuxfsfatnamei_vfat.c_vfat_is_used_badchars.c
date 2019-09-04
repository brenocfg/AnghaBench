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
typedef  char wchar_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ vfat_bad_char (char const) ; 

__attribute__((used)) static inline int vfat_is_used_badchars(const wchar_t *s, int len)
{
	int i;

	for (i = 0; i < len; i++)
		if (vfat_bad_char(s[i]))
			return -EINVAL;

	if (s[i - 1] == ' ') /* last character cannot be space */
		return -EINVAL;

	return 0;
}