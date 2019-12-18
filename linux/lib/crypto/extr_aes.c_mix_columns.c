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
 int mul_by_x (int) ; 
 int ror32 (int,int) ; 

__attribute__((used)) static u32 mix_columns(u32 x)
{
	/*
	 * Perform the following matrix multiplication in GF(2^8)
	 *
	 * | 0x2 0x3 0x1 0x1 |   | x[0] |
	 * | 0x1 0x2 0x3 0x1 |   | x[1] |
	 * | 0x1 0x1 0x2 0x3 | x | x[2] |
	 * | 0x3 0x1 0x1 0x2 |   | x[3] |
	 */
	u32 y = mul_by_x(x) ^ ror32(x, 16);

	return y ^ ror32(x ^ y, 8);
}