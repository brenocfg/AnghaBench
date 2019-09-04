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
struct scsi_device {int /*<<< orphan*/  id; TYPE_1__* host; } ;
struct ahd_softc {int dummy; } ;
struct ahd_linux_device {int openings; scalar_t__ maxtags; } ;
struct TYPE_2__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahd_name (struct ahd_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  memset (struct ahd_linux_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ahd_linux_device* scsi_transport_device_data (struct scsi_device*) ; 

__attribute__((used)) static int
ahd_linux_slave_alloc(struct scsi_device *sdev)
{
	struct	ahd_softc *ahd =
		*((struct ahd_softc **)sdev->host->hostdata);
	struct ahd_linux_device *dev;

	if (bootverbose)
		printk("%s: Slave Alloc %d\n", ahd_name(ahd), sdev->id);

	dev = scsi_transport_device_data(sdev);
	memset(dev, 0, sizeof(*dev));

	/*
	 * We start out life using untagged
	 * transactions of which we allow one.
	 */
	dev->openings = 1;

	/*
	 * Set maxtags to 0.  This will be changed if we
	 * later determine that we are dealing with
	 * a tagged queuing capable device.
	 */
	dev->maxtags = 0;
	
	return (0);
}