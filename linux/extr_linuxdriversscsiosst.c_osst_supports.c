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
struct scsi_device {int /*<<< orphan*/  rev; int /*<<< orphan*/  model; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
#define  SIGS_FROM_OSST 128 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int osst_supports(struct scsi_device * SDp)
{
	struct	osst_support_data {
		char *vendor;
		char *model;
		char *rev;
		char *driver_hint; /* Name of the correct driver, NULL if unknown */
	};

static	struct	osst_support_data support_list[] = {
		/* {"XXX", "Yy-", "", NULL},  example */
		SIGS_FROM_OSST,
		{NULL, }};

	struct	osst_support_data *rp;

	/* We are willing to drive OnStream SC-x0 as well as the
	 * 	 * IDE, ParPort, FireWire, USB variants, if accessible by
	 * 	 	 * emulation layer (ide-scsi, usb-storage, ...) */

	for (rp=&(support_list[0]); rp->vendor != NULL; rp++)
		if (!strncmp(rp->vendor, SDp->vendor, strlen(rp->vendor)) &&
		    !strncmp(rp->model, SDp->model, strlen(rp->model)) &&
		    !strncmp(rp->rev, SDp->rev, strlen(rp->rev))) 
			return 1;
	return 0;
}