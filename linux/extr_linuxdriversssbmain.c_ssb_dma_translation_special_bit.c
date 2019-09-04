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
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ coreid; } ;
struct ssb_device {TYPE_2__ id; TYPE_1__* bus; } ;
struct TYPE_3__ {int chip_id; } ;

/* Variables and functions */
 scalar_t__ SSB_DEV_80211 ; 

__attribute__((used)) static bool ssb_dma_translation_special_bit(struct ssb_device *dev)
{
	u16 chip_id = dev->bus->chip_id;

	if (dev->id.coreid == SSB_DEV_80211) {
		return (chip_id == 0x4322 || chip_id == 43221 ||
			chip_id == 43231 || chip_id == 43222);
	}

	return false;
}