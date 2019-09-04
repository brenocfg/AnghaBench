#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {struct net_device* dev; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384X_OUTW (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HFA384X_PCICOR_OFF ; 
 int /*<<< orphan*/  HFA384X_PCIHCR_OFF ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void prism2_pci_genesis_reset(local_info_t *local, int hcr)
{
	struct net_device *dev = local->dev;

	HFA384X_OUTW(0x00C5, HFA384X_PCICOR_OFF);
	mdelay(10);
	HFA384X_OUTW(hcr, HFA384X_PCIHCR_OFF);
	mdelay(10);
	HFA384X_OUTW(0x0045, HFA384X_PCICOR_OFF);
	mdelay(10);
}