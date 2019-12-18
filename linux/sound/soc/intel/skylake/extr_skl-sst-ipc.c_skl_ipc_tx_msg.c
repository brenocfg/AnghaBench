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
struct sst_generic_ipc {int /*<<< orphan*/  dsp; } ;
struct skl_ipc_header {int extension; int primary; } ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  data; int /*<<< orphan*/  header; } ;
struct ipc_message {TYPE_1__ tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKL_ADSP_REG_HIPCI ; 
 int /*<<< orphan*/  SKL_ADSP_REG_HIPCIE ; 
 int SKL_ADSP_REG_HIPCI_BUSY ; 
 int /*<<< orphan*/  sst_dsp_outbox_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sst_dsp_shim_write_unlocked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void skl_ipc_tx_msg(struct sst_generic_ipc *ipc, struct ipc_message *msg)
{
	struct skl_ipc_header *header = (struct skl_ipc_header *)(&msg->tx.header);

	if (msg->tx.size)
		sst_dsp_outbox_write(ipc->dsp, msg->tx.data, msg->tx.size);
	sst_dsp_shim_write_unlocked(ipc->dsp, SKL_ADSP_REG_HIPCIE,
						header->extension);
	sst_dsp_shim_write_unlocked(ipc->dsp, SKL_ADSP_REG_HIPCI,
		header->primary | SKL_ADSP_REG_HIPCI_BUSY);
}