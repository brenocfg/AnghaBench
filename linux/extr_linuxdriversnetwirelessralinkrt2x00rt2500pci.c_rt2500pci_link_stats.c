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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;
struct link_qual {void* false_cca; void* rx_failed; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNT0 ; 
 int /*<<< orphan*/  CNT0_FCS_ERROR ; 
 int /*<<< orphan*/  CNT3 ; 
 int /*<<< orphan*/  CNT3_FALSE_CCA ; 
 void* rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2500pci_link_stats(struct rt2x00_dev *rt2x00dev,
				 struct link_qual *qual)
{
	u32 reg;

	/*
	 * Update FCS error count from register.
	 */
	reg = rt2x00mmio_register_read(rt2x00dev, CNT0);
	qual->rx_failed = rt2x00_get_field32(reg, CNT0_FCS_ERROR);

	/*
	 * Update False CCA count from register.
	 */
	reg = rt2x00mmio_register_read(rt2x00dev, CNT3);
	qual->false_cca = rt2x00_get_field32(reg, CNT3_FALSE_CCA);
}