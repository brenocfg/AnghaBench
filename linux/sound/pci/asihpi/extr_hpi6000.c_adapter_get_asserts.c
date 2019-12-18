#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int count; int dsp_index; scalar_t__ dsp_msg_addr; int /*<<< orphan*/  sz_message; scalar_t__ p2; scalar_t__ p1; } ;
struct TYPE_5__ {TYPE_1__ assert; } ;
struct TYPE_6__ {TYPE_2__ ax; } ;
struct hpi_response {scalar_t__ error; TYPE_3__ u; } ;
struct hpi_message {int dummy; } ;
struct hpi_adapter_obj {int dummy; } ;

/* Variables and functions */
 int gw_pci_read_asserts ; 
 scalar_t__ gw_pci_write_asserts ; 
 int /*<<< orphan*/  hw_message (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void adapter_get_asserts(struct hpi_adapter_obj *pao,
	struct hpi_message *phm, struct hpi_response *phr)
{
#ifndef HIDE_PCI_ASSERTS
	/* if we have PCI2040 asserts then collect them */
	if ((gw_pci_read_asserts > 0) || (gw_pci_write_asserts > 0)) {
		phr->u.ax.assert.p1 =
			gw_pci_read_asserts * 100 + gw_pci_write_asserts;
		phr->u.ax.assert.p2 = 0;
		phr->u.ax.assert.count = 1;	/* assert count */
		phr->u.ax.assert.dsp_index = -1;	/* "dsp index" */
		strcpy(phr->u.ax.assert.sz_message, "PCI2040 error");
		phr->u.ax.assert.dsp_msg_addr = 0;
		gw_pci_read_asserts = 0;
		gw_pci_write_asserts = 0;
		phr->error = 0;
	} else
#endif
		hw_message(pao, phm, phr);	/*get DSP asserts */

	return;
}