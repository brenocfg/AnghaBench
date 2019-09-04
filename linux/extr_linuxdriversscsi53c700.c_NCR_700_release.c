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
struct Scsi_Host {scalar_t__* hostdata; } ;
struct NCR_700_Host_Parameters {int /*<<< orphan*/  pScript; int /*<<< orphan*/  script; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_NON_CONSISTENT ; 
 int /*<<< orphan*/  TOTAL_MEM_SIZE ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
NCR_700_release(struct Scsi_Host *host)
{
	struct NCR_700_Host_Parameters *hostdata = 
		(struct NCR_700_Host_Parameters *)host->hostdata[0];

	dma_free_attrs(hostdata->dev, TOTAL_MEM_SIZE, hostdata->script,
		       hostdata->pScript, DMA_ATTR_NON_CONSISTENT);
	return 1;
}