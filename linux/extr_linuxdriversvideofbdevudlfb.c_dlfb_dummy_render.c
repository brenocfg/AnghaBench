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

__attribute__((used)) static char *dlfb_dummy_render(char *buf)
{
	*buf++ = 0xAF;
	*buf++ = 0x6A; /* copy */
	*buf++ = 0x00; /* from address*/
	*buf++ = 0x00;
	*buf++ = 0x00;
	*buf++ = 0x01; /* one pixel */
	*buf++ = 0x00; /* to address */
	*buf++ = 0x00;
	*buf++ = 0x00;
	return buf;
}