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
struct TYPE_2__ {int /*<<< orphan*/  func; int /*<<< orphan*/  dev; } ;
union win_slot_encoding {scalar_t__ slot; TYPE_1__ bits; } ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_FUNC (int) ; 
 int /*<<< orphan*/  PCI_SLOT (int) ; 

__attribute__((used)) static u32 devfn_to_wslot(int devfn)
{
	union win_slot_encoding wslot;

	wslot.slot = 0;
	wslot.bits.dev = PCI_SLOT(devfn);
	wslot.bits.func = PCI_FUNC(devfn);

	return wslot.slot;
}