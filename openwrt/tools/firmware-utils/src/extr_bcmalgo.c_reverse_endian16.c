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
typedef  int uint16_t ;

/* Variables and functions */

uint16_t reverse_endian16 ( uint16_t data )
{
#ifdef ENDIAN_REVERSE_NEEDED
	return 0 | ( data & 0x00ff ) << 8
	       | ( data & 0xff00 ) >> 8;
#else
	return data;
#endif
}