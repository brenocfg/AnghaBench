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
typedef  int uint64 ;

/* Variables and functions */

void
print_tar_number(char *s, int len, uint64 val)
{
	if (val < (((uint64) 1) << ((len - 1) * 3)))
	{
		/* Use octal with trailing space */
		s[--len] = ' ';
		while (len)
		{
			s[--len] = (val & 7) + '0';
			val >>= 3;
		}
	}
	else
	{
		/* Use base-256 with leading \200 */
		s[0] = '\200';
		while (len > 1)
		{
			s[--len] = (val & 255);
			val >>= 8;
		}
	}
}