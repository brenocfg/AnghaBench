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
struct scsi_cmnd {int dummy; } ;
struct pqi_io_request {struct scsi_cmnd* scmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  pqi_free_io_request (struct pqi_io_request*) ; 
 int /*<<< orphan*/  pqi_scsi_done (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 

__attribute__((used)) static void pqi_raid_io_complete(struct pqi_io_request *io_request,
	void *context)
{
	struct scsi_cmnd *scmd;

	scmd = io_request->scmd;
	pqi_free_io_request(io_request);
	scsi_dma_unmap(scmd);
	pqi_scsi_done(scmd);
}