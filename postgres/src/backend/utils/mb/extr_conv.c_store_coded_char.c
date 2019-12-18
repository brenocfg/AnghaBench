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

__attribute__((used)) static inline unsigned char *
store_coded_char(unsigned char *dest, uint32 code)
{
	if (code & 0xff000000)
		*dest++ = code >> 24;
	if (code & 0x00ff0000)
		*dest++ = code >> 16;
	if (code & 0x0000ff00)
		*dest++ = code >> 8;
	if (code & 0x000000ff)
		*dest++ = code;
	return dest;
}