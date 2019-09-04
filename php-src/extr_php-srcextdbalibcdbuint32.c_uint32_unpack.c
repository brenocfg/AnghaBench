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

void uint32_unpack(const char *in, uint32 *out)
{
	*out = (((uint32)(unsigned char)in[3])<<24) |
	       (((uint32)(unsigned char)in[2])<<16) |
	       (((uint32)(unsigned char)in[1])<<8) |
	       (((uint32)(unsigned char)in[0]));
}