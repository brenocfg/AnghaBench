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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */

char *
cdf_u16tos8(char *buf, size_t len, const uint16_t *p)
{
	size_t i;
	for (i = 0; i < len && p[i]; i++)
		buf[i] = (char)p[i];
	buf[i] = '\0';
	return buf;
}