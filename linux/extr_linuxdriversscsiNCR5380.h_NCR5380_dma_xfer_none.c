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
struct NCR5380_hostdata {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int NCR5380_dma_xfer_none(struct NCR5380_hostdata *hostdata,
                                        struct scsi_cmnd *cmd)
{
	return 0;
}