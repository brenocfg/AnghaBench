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
struct mmp_dma_data {TYPE_1__* dma_res; int /*<<< orphan*/  ssp_id; } ;
struct dma_chan {scalar_t__ chan_id; TYPE_2__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ start; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool filter(struct dma_chan *chan, void *param)
{
	struct mmp_dma_data *dma_data = param;
	bool found = false;
	char *devname;

	devname = kasprintf(GFP_KERNEL, "%s.%d", dma_data->dma_res->name,
		dma_data->ssp_id);
	if ((strcmp(dev_name(chan->device->dev), devname) == 0) &&
		(chan->chan_id == dma_data->dma_res->start)) {
		found = true;
	}

	kfree(devname);
	return found;
}