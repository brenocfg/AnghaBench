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
struct uhci_hcd {scalar_t__ (* check_and_reset_hc ) (struct uhci_hcd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  finish_reset (struct uhci_hcd*) ; 
 scalar_t__ stub1 (struct uhci_hcd*) ; 

__attribute__((used)) static void check_and_reset_hc(struct uhci_hcd *uhci)
{
	if (uhci->check_and_reset_hc(uhci))
		finish_reset(uhci);
}