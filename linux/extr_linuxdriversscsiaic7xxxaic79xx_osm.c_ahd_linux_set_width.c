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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct scsi_target {scalar_t__ channel; int /*<<< orphan*/  id; TYPE_1__ dev; } ;
struct ahd_softc {int dummy; } ;
struct ahd_devinfo {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  this_id; scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_TRANS_GOAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ROLE_INITIATOR ; 
 int /*<<< orphan*/  ahd_compile_devinfo (struct ahd_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_lock (struct ahd_softc*,unsigned long*) ; 
 int /*<<< orphan*/  ahd_set_width (struct ahd_softc*,struct ahd_devinfo*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_unlock (struct ahd_softc*,unsigned long*) ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ahd_linux_set_width(struct scsi_target *starget, int width)
{
	struct Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	struct ahd_softc *ahd = *((struct ahd_softc **)shost->hostdata);
	struct ahd_devinfo devinfo;
	unsigned long flags;

	ahd_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	ahd_lock(ahd, &flags);
	ahd_set_width(ahd, &devinfo, width, AHD_TRANS_GOAL, FALSE);
	ahd_unlock(ahd, &flags);
}