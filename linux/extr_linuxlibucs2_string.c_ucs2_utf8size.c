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
typedef  int ucs2_char_t ;
typedef  int u16 ;

/* Variables and functions */

unsigned long
ucs2_utf8size(const ucs2_char_t *src)
{
	unsigned long i;
	unsigned long j = 0;

	for (i = 0; src[i]; i++) {
		u16 c = src[i];

		if (c >= 0x800)
			j += 3;
		else if (c >= 0x80)
			j += 2;
		else
			j += 1;
	}

	return j;
}