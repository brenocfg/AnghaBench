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
struct snic_req_info {int /*<<< orphan*/  dr_req; int /*<<< orphan*/  abort_req; int /*<<< orphan*/  req; } ;
struct TYPE_3__ {scalar_t__ sense_addr; } ;
struct TYPE_4__ {TYPE_1__ icmnd; } ;
struct snic_host_req {TYPE_2__ u; } ;
struct snic {int /*<<< orphan*/  pdev; int /*<<< orphan*/  shost; } ;
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int CMD_FLAGS (struct scsi_cmnd*) ; 
 scalar_t__ CMD_STATE (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  SNIC_BUG_ON (int) ; 
 int SNIC_DEV_RST_NOTSUP ; 
 int SNIC_DEV_RST_TERM_ISSUED ; 
 scalar_t__ SNIC_IOREQ_ABTS_COMPLETE ; 
 scalar_t__ SNIC_IOREQ_COMPLETE ; 
 scalar_t__ SNIC_IOREQ_LR_COMPLETE ; 
 int SNIC_IO_INTERNAL_TERM_ISSUED ; 
 int SNIC_SCSI_CLEANUP ; 
 int /*<<< orphan*/  SNIC_SCSI_DBG (int /*<<< orphan*/ ,char*,struct scsi_cmnd*,int /*<<< orphan*/ ,struct snic_req_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snic_host_req* rqi_to_req (struct snic_req_info*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  snic_cmd_tag (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  snic_ioreq_state_to_str (scalar_t__) ; 
 int /*<<< orphan*/  snic_req_free (struct snic*,struct snic_req_info*) ; 

__attribute__((used)) static void
snic_release_req_buf(struct snic *snic,
		   struct snic_req_info *rqi,
		   struct scsi_cmnd *sc)
{
	struct snic_host_req *req = rqi_to_req(rqi);

	/* Freeing cmd without marking completion, not okay */
	SNIC_BUG_ON(!((CMD_STATE(sc) == SNIC_IOREQ_COMPLETE) ||
		      (CMD_STATE(sc) == SNIC_IOREQ_ABTS_COMPLETE) ||
		      (CMD_FLAGS(sc) & SNIC_DEV_RST_NOTSUP) ||
		      (CMD_FLAGS(sc) & SNIC_IO_INTERNAL_TERM_ISSUED) ||
		      (CMD_FLAGS(sc) & SNIC_DEV_RST_TERM_ISSUED) ||
		      (CMD_FLAGS(sc) & SNIC_SCSI_CLEANUP) ||
		      (CMD_STATE(sc) == SNIC_IOREQ_LR_COMPLETE)));

	SNIC_SCSI_DBG(snic->shost,
		      "Rel_req:sc %p:tag %x:rqi %p:ioreq %p:abt %p:dr %p: state %s:flags 0x%llx\n",
		      sc, snic_cmd_tag(sc), rqi, rqi->req, rqi->abort_req,
		      rqi->dr_req, snic_ioreq_state_to_str(CMD_STATE(sc)),
		      CMD_FLAGS(sc));

	if (req->u.icmnd.sense_addr)
		pci_unmap_single(snic->pdev,
				 le64_to_cpu(req->u.icmnd.sense_addr),
				 SCSI_SENSE_BUFFERSIZE,
				 PCI_DMA_FROMDEVICE);

	scsi_dma_unmap(sc);

	snic_req_free(snic, rqi);
}