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
struct uhci_hcd {int (* global_suspend_mode_is_broken ) (struct uhci_hcd*) ;} ;

/* Variables and functions */
 int stub1 (struct uhci_hcd*) ; 

__attribute__((used)) static int global_suspend_mode_is_broken(struct uhci_hcd *uhci)
{
	return uhci->global_suspend_mode_is_broken ?
		uhci->global_suspend_mode_is_broken(uhci) : 0;
}