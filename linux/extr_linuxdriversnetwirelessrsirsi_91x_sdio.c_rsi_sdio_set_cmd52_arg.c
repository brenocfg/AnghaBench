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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 rsi_sdio_set_cmd52_arg(bool rw,
				  u8 func,
				  u8 raw,
				  u32 address,
				  u8 writedata)
{
	return ((rw & 1) << 31) | ((func & 0x7) << 28) |
		((raw & 1) << 27) | (1 << 26) |
		((address & 0x1FFFF) << 9) | (1 << 8) |
		(writedata & 0xFF);
}