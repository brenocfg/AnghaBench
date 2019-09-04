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
typedef  int /*<<< orphan*/  u32 ;
struct ohci_hcd {TYPE_2__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__ roothub; } ;

/* Variables and functions */
 int /*<<< orphan*/  ohci_readl (struct ohci_hcd*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 roothub_status (struct ohci_hcd *hc)
	{ return ohci_readl (hc, &hc->regs->roothub.status); }