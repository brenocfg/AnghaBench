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
struct scsi_qla_host {void* iface_ipv6_1; int /*<<< orphan*/  host; void* iface_ipv6_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_IFACE_TYPE_IPV6 ; 
 int /*<<< orphan*/  KERN_ERR ; 
 void* iscsi_create_iface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 
 int /*<<< orphan*/  qla4xxx_iscsi_transport ; 

__attribute__((used)) static void qla4xxx_create_ipv6_iface(struct scsi_qla_host *ha)
{
	if (!ha->iface_ipv6_0)
		/* IPv6 iface-0 */
		ha->iface_ipv6_0 = iscsi_create_iface(ha->host,
						      &qla4xxx_iscsi_transport,
						      ISCSI_IFACE_TYPE_IPV6, 0,
						      0);
	if (!ha->iface_ipv6_0)
		ql4_printk(KERN_ERR, ha, "Could not create IPv6 iSCSI "
			   "iface0.\n");

	if (!ha->iface_ipv6_1)
		/* IPv6 iface-1 */
		ha->iface_ipv6_1 = iscsi_create_iface(ha->host,
						      &qla4xxx_iscsi_transport,
						      ISCSI_IFACE_TYPE_IPV6, 1,
						      0);
	if (!ha->iface_ipv6_1)
		ql4_printk(KERN_ERR, ha, "Could not create IPv6 iSCSI "
			   "iface1.\n");
}