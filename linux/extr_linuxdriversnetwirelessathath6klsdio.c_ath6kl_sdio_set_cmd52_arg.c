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

__attribute__((used)) static inline void ath6kl_sdio_set_cmd52_arg(u32 *arg, u8 write, u8 raw,
					     unsigned int address,
					     unsigned char val)
{
	const u8 func = 0;

	*arg = ((write & 1) << 31) |
	       ((func & 0x7) << 28) |
	       ((raw & 1) << 27) |
	       (1 << 26) |
	       ((address & 0x1FFFF) << 9) |
	       (1 << 8) |
	       (val & 0xFF);
}