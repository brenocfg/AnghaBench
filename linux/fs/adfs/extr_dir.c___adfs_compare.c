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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ adfs_tolower (char const) ; 

__attribute__((used)) static int __adfs_compare(const unsigned char *qstr, u32 qlen,
			  const char *str, u32 len)
{
	u32 i;

	if (qlen != len)
		return 1;

	for (i = 0; i < qlen; i++)
		if (adfs_tolower(qstr[i]) != adfs_tolower(str[i]))
			return 1;

	return 0;
}