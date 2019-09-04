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
struct pqi_scsi_dev {int raid_bypass_enabled; int aio_enabled; } ;
struct pqi_io_request {TYPE_2__* scmd; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct pqi_scsi_dev* hostdata; } ;

/* Variables and functions */

__attribute__((used)) static inline void pqi_aio_path_disabled(struct pqi_io_request *io_request)
{
	struct pqi_scsi_dev *device;

	device = io_request->scmd->device->hostdata;
	device->raid_bypass_enabled = false;
	device->aio_enabled = false;
}