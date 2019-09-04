#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rt2x00lib_conf {int /*<<< orphan*/ * conf; } ;
struct rt2x00_dev {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CONF_CHANGE_PS ; 
 int /*<<< orphan*/  rt61pci_config (struct rt2x00_dev*,struct rt2x00lib_conf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt61pci_wakeup(struct rt2x00_dev *rt2x00dev)
{
	struct rt2x00lib_conf libconf = { .conf = &rt2x00dev->hw->conf };

	rt61pci_config(rt2x00dev, &libconf, IEEE80211_CONF_CHANGE_PS);
}