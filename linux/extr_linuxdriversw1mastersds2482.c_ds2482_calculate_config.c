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

/* Variables and functions */
 int DS2482_REG_CFG_APU ; 
 scalar_t__ ds2482_active_pullup ; 

__attribute__((used)) static inline u8 ds2482_calculate_config(u8 conf)
{
	if (ds2482_active_pullup)
		conf |= DS2482_REG_CFG_APU;

	return conf | ((~conf & 0x0f) << 4);
}