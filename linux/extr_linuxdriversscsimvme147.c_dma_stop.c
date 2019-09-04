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
struct scsi_cmnd {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {scalar_t__ dma_cntrl; } ;

/* Variables and functions */
 TYPE_1__* m147_pcc ; 

__attribute__((used)) static void dma_stop(struct Scsi_Host *instance, struct scsi_cmnd *SCpnt,
		     int status)
{
	m147_pcc->dma_cntrl = 0;
}