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
 scalar_t__ IS_HIGHBIT_SET (unsigned char const) ; 
 unsigned char const SS2 ; 
 unsigned char const SS3 ; 

__attribute__((used)) static int
pg_euctw_mblen(const unsigned char *s)
{
	int			len;

	if (*s == SS2)
		len = 4;
	else if (*s == SS3)
		len = 3;
	else if (IS_HIGHBIT_SET(*s))
		len = 2;
	else
		len = 1;
	return len;
}