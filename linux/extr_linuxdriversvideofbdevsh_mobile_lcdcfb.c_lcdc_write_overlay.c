#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sh_mobile_lcdc_overlay {TYPE_2__* channel; } ;
struct TYPE_4__ {TYPE_1__* lcdc; } ;
struct TYPE_3__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SIDE_B_OFFSET ; 
 int /*<<< orphan*/  iowrite32 (unsigned long,scalar_t__) ; 

__attribute__((used)) static void lcdc_write_overlay(struct sh_mobile_lcdc_overlay *ovl,
			       int reg, unsigned long data)
{
	iowrite32(data, ovl->channel->lcdc->base + reg);
	iowrite32(data, ovl->channel->lcdc->base + reg + SIDE_B_OFFSET);
}