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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */

__attribute__((used)) static uint8 *
render_newlen(uint8 *h, int len)
{
	if (len <= 191)
	{
		*h++ = len & 255;
	}
	else if (len > 191 && len <= 8383)
	{
		*h++ = ((len - 192) >> 8) + 192;
		*h++ = (len - 192) & 255;
	}
	else
	{
		*h++ = 255;
		*h++ = (len >> 24) & 255;
		*h++ = (len >> 16) & 255;
		*h++ = (len >> 8) & 255;
		*h++ = len & 255;
	}
	return h;
}