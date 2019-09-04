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
struct ohci_hcd {int rh_state; } ;

/* Variables and functions */
#define  OHCI_RH_HALTED 130 
#define  OHCI_RH_RUNNING 129 
#define  OHCI_RH_SUSPENDED 128 

__attribute__((used)) static const char *rh_state_string(struct ohci_hcd *ohci)
{
	switch (ohci->rh_state) {
	case OHCI_RH_HALTED:
		return "halted";
	case OHCI_RH_SUSPENDED:
		return "suspended";
	case OHCI_RH_RUNNING:
		return "running";
	}
	return "?";
}