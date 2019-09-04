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
typedef  scalar_t__ u32 ;
struct ohci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ohci_dbg_sw (struct ohci_hcd*,char**,unsigned int*,char*,char*,scalar_t__) ; 

__attribute__((used)) static void maybe_print_eds (
	struct ohci_hcd *ohci,
	char *label,
	u32 value,
	char **next,
	unsigned *size)
{
	if (value)
		ohci_dbg_sw (ohci, next, size, "%s %08x\n", label, value);
}