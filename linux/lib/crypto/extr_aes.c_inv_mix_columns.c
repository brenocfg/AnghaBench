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
 int mix_columns (int) ; 
 int mul_by_x2 (int) ; 
 int ror32 (int,int) ; 

__attribute__((used)) static u32 inv_mix_columns(u32 x)
{
	/*
	 * Perform the following matrix multiplication in GF(2^8)
	 *
	 * | 0xe 0xb 0xd 0x9 |   | x[0] |
	 * | 0x9 0xe 0xb 0xd |   | x[1] |
	 * | 0xd 0x9 0xe 0xb | x | x[2] |
	 * | 0xb 0xd 0x9 0xe |   | x[3] |
	 *
	 * which can conveniently be reduced to
	 *
	 * | 0x2 0x3 0x1 0x1 |   | 0x5 0x0 0x4 0x0 |   | x[0] |
	 * | 0x1 0x2 0x3 0x1 |   | 0x0 0x5 0x0 0x4 |   | x[1] |
	 * | 0x1 0x1 0x2 0x3 | x | 0x4 0x0 0x5 0x0 | x | x[2] |
	 * | 0x3 0x1 0x1 0x2 |   | 0x0 0x4 0x0 0x5 |   | x[3] |
	 */
	u32 y = mul_by_x2(x);

	return mix_columns(x ^ y ^ ror32(y, 16));
}