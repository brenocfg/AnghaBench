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
typedef  int uint8_t ;
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static uint8_t rgb565_to_g16(u16 pixel)
{
	u16 b = pixel & 0x1f;
	u16 g = (pixel & (0x3f << 5)) >> 5;
	u16 r = (pixel & (0x1f << (5 + 6))) >> (5 + 6);

	pixel = (299 * r + 587 * g + 114 * b) / 195;
	if (pixel > 255)
		pixel = 255;
	return (uint8_t)pixel / 16;
}