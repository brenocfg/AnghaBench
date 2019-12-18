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
typedef  int uint32 ;

/* Variables and functions */

__attribute__((used)) static inline uint32
utf8word_to_unicode(uint32 c)
{
	uint32		ucs;

	if (c <= 0x7F)
	{
		ucs = c;
	}
	else if (c <= 0xFFFF)
	{
		ucs = ((c >> 8) & 0x1F) << 6;
		ucs |= c & 0x3F;
	}
	else if (c <= 0xFFFFFF)
	{
		ucs = ((c >> 16) & 0x0F) << 12;
		ucs |= ((c >> 8) & 0x3F) << 6;
		ucs |= c & 0x3F;
	}
	else
	{
		ucs = ((c >> 24) & 0x07) << 18;
		ucs |= ((c >> 16) & 0x3F) << 12;
		ucs |= ((c >> 8) & 0x3F) << 6;
		ucs |= c & 0x3F;
	}

	return ucs;
}