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
struct TYPE_2__ {int this_residual; } ;
struct scsi_cmnd {TYPE_1__ SCp; } ;
struct NCR5380_hostdata {int flags; } ;

/* Variables and functions */
 int FLAG_NO_PSEUDO_DMA ; 

__attribute__((used)) static int macscsi_dma_xfer_len(struct NCR5380_hostdata *hostdata,
                                struct scsi_cmnd *cmd)
{
	if (hostdata->flags & FLAG_NO_PSEUDO_DMA ||
	    cmd->SCp.this_residual < 16)
		return 0;

	return cmd->SCp.this_residual;
}