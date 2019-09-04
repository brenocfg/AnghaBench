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
struct scsi_cmnd {int dummy; } ;
struct megasas_instance {int /*<<< orphan*/  adprecovery; scalar_t__ peerIsPresent; } ;

/* Variables and functions */
 int DID_NO_CONNECT ; 
 int DID_REQUEUE ; 
 scalar_t__ MEGASAS_HBA_OPERATIONAL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct megasas_instance* megasas_get_peer_instance (struct megasas_instance*) ; 

int megasas_check_mpio_paths(struct megasas_instance *instance,
	struct scsi_cmnd *scmd)
{
	struct megasas_instance *peer_instance = NULL;
	int retval = (DID_REQUEUE << 16);

	if (instance->peerIsPresent) {
		peer_instance = megasas_get_peer_instance(instance);
		if ((peer_instance) &&
			(atomic_read(&peer_instance->adprecovery) ==
			MEGASAS_HBA_OPERATIONAL))
			retval = (DID_NO_CONNECT << 16);
	}
	return retval;
}