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
struct scsi_cmnd {scalar_t__ sense_buffer; int /*<<< orphan*/  sc_data_direction; } ;
struct pvscsi_ctx {scalar_t__ sensePA; scalar_t__ dataPA; scalar_t__ sglPA; struct scsi_cmnd* cmd; } ;
struct pvscsi_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 unsigned int SCSI_SENSE_BUFFERSIZE ; 
 unsigned int SGL_SIZE ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 unsigned int scsi_sg_count (struct scsi_cmnd*) ; 

__attribute__((used)) static void pvscsi_unmap_buffers(const struct pvscsi_adapter *adapter,
				 struct pvscsi_ctx *ctx)
{
	struct scsi_cmnd *cmd;
	unsigned bufflen;

	cmd = ctx->cmd;
	bufflen = scsi_bufflen(cmd);

	if (bufflen != 0) {
		unsigned count = scsi_sg_count(cmd);

		if (count != 0) {
			scsi_dma_unmap(cmd);
			if (ctx->sglPA) {
				pci_unmap_single(adapter->dev, ctx->sglPA,
						 SGL_SIZE, PCI_DMA_TODEVICE);
				ctx->sglPA = 0;
			}
		} else
			pci_unmap_single(adapter->dev, ctx->dataPA, bufflen,
					 cmd->sc_data_direction);
	}
	if (cmd->sense_buffer)
		pci_unmap_single(adapter->dev, ctx->sensePA,
				 SCSI_SENSE_BUFFERSIZE, PCI_DMA_FROMDEVICE);
}