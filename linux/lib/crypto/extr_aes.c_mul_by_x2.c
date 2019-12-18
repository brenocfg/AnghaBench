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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 mul_by_x2(u32 w)
{
	u32 x = w & 0x3f3f3f3f;
	u32 y = w & 0x80808080;
	u32 z = w & 0x40404040;

	/* multiply by polynomial 'x^2' (0b100) in GF(2^8) */
	return (x << 2) ^ (y >> 7) * 0x36 ^ (z >> 6) * 0x1b;
}