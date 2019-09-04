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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static u16 ef4_farch_filter_hash(u32 key)
{
	u16 tmp;

	/* First 16 rounds */
	tmp = 0x1fff ^ key >> 16;
	tmp = tmp ^ tmp >> 3 ^ tmp >> 6;
	tmp = tmp ^ tmp >> 9;
	/* Last 16 rounds */
	tmp = tmp ^ tmp << 13 ^ key;
	tmp = tmp ^ tmp >> 3 ^ tmp >> 6;
	return tmp ^ tmp >> 9;
}