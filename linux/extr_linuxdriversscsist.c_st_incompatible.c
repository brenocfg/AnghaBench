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
struct st_reject_data {char* driver_hint; int /*<<< orphan*/ * rev; int /*<<< orphan*/ * model; int /*<<< orphan*/ * vendor; } ;
struct scsi_device {int /*<<< orphan*/  rev; int /*<<< orphan*/  model; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 struct st_reject_data* reject_list ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char * st_incompatible(struct scsi_device* SDp)
{
	struct st_reject_data *rp;

	for (rp=&(reject_list[0]); rp->vendor != NULL; rp++)
		if (!strncmp(rp->vendor, SDp->vendor, strlen(rp->vendor)) &&
		    !strncmp(rp->model, SDp->model, strlen(rp->model)) &&
		    !strncmp(rp->rev, SDp->rev, strlen(rp->rev))) {
			if (rp->driver_hint)
				return rp->driver_hint;
			else
				return "unknown";
		}
	return NULL;
}