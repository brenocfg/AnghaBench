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
struct scsi_qla_host {int /*<<< orphan*/ * iface_ipv6_1; int /*<<< orphan*/ * iface_ipv6_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_destroy_iface (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qla4xxx_destroy_ipv6_iface(struct scsi_qla_host *ha)
{
	if (ha->iface_ipv6_0) {
		iscsi_destroy_iface(ha->iface_ipv6_0);
		ha->iface_ipv6_0 = NULL;
	}
	if (ha->iface_ipv6_1) {
		iscsi_destroy_iface(ha->iface_ipv6_1);
		ha->iface_ipv6_1 = NULL;
	}
}