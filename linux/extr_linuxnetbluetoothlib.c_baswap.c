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
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */

void baswap(bdaddr_t *dst, const bdaddr_t *src)
{
	const unsigned char *s = (const unsigned char *)src;
	unsigned char *d = (unsigned char *)dst;
	unsigned int i;

	for (i = 0; i < 6; i++)
		d[i] = s[5 - i];
}