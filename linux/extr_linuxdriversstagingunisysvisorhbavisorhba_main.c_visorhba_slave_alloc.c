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
struct visorhba_devdata {int dummy; } ;
struct visordisk_info {struct scsi_device* sdev; } ;
struct scsi_device {struct visordisk_info* hostdata; scalar_t__ host; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct visordisk_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int visorhba_slave_alloc(struct scsi_device *scsidev)
{
	/* this is called by the midlayer before scan for new devices --
	 * LLD can alloc any struct & do init if needed.
	 */
	struct visordisk_info *vdisk;
	struct visorhba_devdata *devdata;
	struct Scsi_Host *scsihost = (struct Scsi_Host *)scsidev->host;

	/* already allocated return success */
	if (scsidev->hostdata)
		return 0;

	/* even though we errored, treat as success */
	devdata = (struct visorhba_devdata *)scsihost->hostdata;
	if (!devdata)
		return 0;

	vdisk = kzalloc(sizeof(*vdisk), GFP_ATOMIC);
	if (!vdisk)
		return -ENOMEM;

	vdisk->sdev = scsidev;
	scsidev->hostdata = vdisk;
	return 0;
}