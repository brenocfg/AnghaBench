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
struct owl_pinctrl {int base; } ;

/* Variables and functions */
 int readl_relaxed (int) ; 

__attribute__((used)) static u32 owl_read_field(struct owl_pinctrl *pctrl, u32 reg,
				u32 bit, u32 width)
{
	u32 tmp, mask;

	tmp = readl_relaxed(pctrl->base + reg);
	mask = (1 << width) - 1;

	return (tmp >> bit) & mask;
}