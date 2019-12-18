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
typedef  scalar_t__ u32 ;
struct sprd_mcdt_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MCDT_CH0_RXD ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void sprd_mcdt_adc_read_fifo(struct sprd_mcdt_dev *mcdt, u8 channel,
				    u32 *val)
{
	u32 reg = MCDT_CH0_RXD + channel * 4;

	*val = readl_relaxed(mcdt->base + reg);
}