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
struct iscsi_cls_host {int /*<<< orphan*/  port_state; } ;
struct beiscsi_hba {int /*<<< orphan*/  state; } ;
struct Scsi_Host {struct iscsi_cls_host* shost_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_HBA_LINK_UP ; 
 int /*<<< orphan*/  ISCSI_PORT_STATE_DOWN ; 
 int /*<<< orphan*/  ISCSI_PORT_STATE_UP ; 
 struct beiscsi_hba* iscsi_host_priv (struct Scsi_Host*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void beiscsi_get_port_state(struct Scsi_Host *shost)
{
	struct beiscsi_hba *phba = iscsi_host_priv(shost);
	struct iscsi_cls_host *ihost = shost->shost_data;

	ihost->port_state = test_bit(BEISCSI_HBA_LINK_UP, &phba->state) ?
		ISCSI_PORT_STATE_UP : ISCSI_PORT_STATE_DOWN;
}