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
struct fc_vport_identifiers {int dummy; } ;
struct fc_vport {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; } ;

/* Variables and functions */
 int fc_vport_setup (struct Scsi_Host*,int,int /*<<< orphan*/ *,struct fc_vport_identifiers*,struct fc_vport**) ; 

struct fc_vport *
fc_vport_create(struct Scsi_Host *shost, int channel,
	struct fc_vport_identifiers *ids)
{
	int stat;
	struct fc_vport *vport;

	stat = fc_vport_setup(shost, channel, &shost->shost_gendev,
		 ids, &vport);
	return stat ? NULL : vport;
}