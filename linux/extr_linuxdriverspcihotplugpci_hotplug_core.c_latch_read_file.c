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
typedef  int u8 ;
struct pci_slot {int /*<<< orphan*/  hotplug; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int get_latch_status (int /*<<< orphan*/ ,int*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t latch_read_file(struct pci_slot *pci_slot, char *buf)
{
	int retval;
	u8 value;

	retval = get_latch_status(pci_slot->hotplug, &value);
	if (retval)
		return retval;

	return sprintf(buf, "%d\n", value);
}