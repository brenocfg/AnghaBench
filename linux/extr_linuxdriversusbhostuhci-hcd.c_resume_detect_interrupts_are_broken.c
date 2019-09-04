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
struct uhci_hcd {int (* resume_detect_interrupts_are_broken ) (struct uhci_hcd*) ;} ;

/* Variables and functions */
 scalar_t__ ignore_oc ; 
 int stub1 (struct uhci_hcd*) ; 
 scalar_t__ uhci_is_aspeed (struct uhci_hcd*) ; 

__attribute__((used)) static int resume_detect_interrupts_are_broken(struct uhci_hcd *uhci)
{
	/*
	 * If we have to ignore overcurrent events then almost by definition
	 * we can't depend on resume-detect interrupts.
	 *
	 * Those interrupts also don't seem to work on ASpeed SoCs.
	 */
	if (ignore_oc || uhci_is_aspeed(uhci))
		return 1;

	return uhci->resume_detect_interrupts_are_broken ?
		uhci->resume_detect_interrupts_are_broken(uhci) : 0;
}