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
struct scsi_dh_blist {char const* driver; scalar_t__ model; scalar_t__ vendor; } ;
struct scsi_device {int /*<<< orphan*/  model; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 scalar_t__ scsi_device_tpgs (struct scsi_device*) ; 
 struct scsi_dh_blist* scsi_dh_blist ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
scsi_dh_find_driver(struct scsi_device *sdev)
{
	const struct scsi_dh_blist *b;

	if (scsi_device_tpgs(sdev))
		return "alua";

	for (b = scsi_dh_blist; b->vendor; b++) {
		if (!strncmp(sdev->vendor, b->vendor, strlen(b->vendor)) &&
		    !strncmp(sdev->model, b->model, strlen(b->model))) {
			return b->driver;
		}
	}
	return NULL;
}