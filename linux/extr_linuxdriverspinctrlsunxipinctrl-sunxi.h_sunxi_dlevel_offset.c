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
 int DLEVEL_PINS_BITS ; 
 int DLEVEL_PINS_PER_REG ; 

__attribute__((used)) static inline u32 sunxi_dlevel_offset(u16 pin)
{
	u32 pin_num = pin % DLEVEL_PINS_PER_REG;
	return pin_num * DLEVEL_PINS_BITS;
}