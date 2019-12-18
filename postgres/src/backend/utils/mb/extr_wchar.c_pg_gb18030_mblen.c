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
 int /*<<< orphan*/  IS_HIGHBIT_SET (unsigned char const) ; 

__attribute__((used)) static int
pg_gb18030_mblen(const unsigned char *s)
{
	int			len;

	if (!IS_HIGHBIT_SET(*s))
		len = 1;				/* ASCII */
	else if (*(s + 1) >= 0x30 && *(s + 1) <= 0x39)
		len = 4;
	else
		len = 2;
	return len;
}