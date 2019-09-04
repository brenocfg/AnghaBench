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
struct lpfc_vport {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_host_symbolic_name (struct Scsi_Host*) ; 
 int /*<<< orphan*/  lpfc_vport_symbolic_node_name (struct lpfc_vport*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lpfc_get_host_symbolic_name(struct Scsi_Host *shost)
{
	struct lpfc_vport *vport = (struct lpfc_vport *)shost->hostdata;

	lpfc_vport_symbolic_node_name(vport, fc_host_symbolic_name(shost),
				      sizeof fc_host_symbolic_name(shost));
}