#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * s6_addr32; } ;
struct TYPE_4__ {TYPE_1__ ipv6_default_router_addr; } ;
struct scsi_qla_host {TYPE_2__ ip_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void qla4xxx_default_router_changed(struct scsi_qla_host *ha,
					   uint32_t *mbox_sts)
{
	memcpy(&ha->ip_config.ipv6_default_router_addr.s6_addr32[0],
	       &mbox_sts[2], sizeof(uint32_t));
	memcpy(&ha->ip_config.ipv6_default_router_addr.s6_addr32[1],
	       &mbox_sts[3], sizeof(uint32_t));
	memcpy(&ha->ip_config.ipv6_default_router_addr.s6_addr32[2],
	       &mbox_sts[4], sizeof(uint32_t));
	memcpy(&ha->ip_config.ipv6_default_router_addr.s6_addr32[3],
	       &mbox_sts[5], sizeof(uint32_t));
}