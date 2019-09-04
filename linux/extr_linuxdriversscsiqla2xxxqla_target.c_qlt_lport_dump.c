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
typedef  int /*<<< orphan*/  u64 ;
struct scsi_qla_host {int /*<<< orphan*/ * port_name; int /*<<< orphan*/ * node_name; } ;

/* Variables and functions */
 int WWN_SIZE ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static void qlt_lport_dump(struct scsi_qla_host *vha, u64 wwpn,
	unsigned char *b)
{
	int i;

	pr_debug("qla2xxx HW vha->node_name: ");
	for (i = 0; i < WWN_SIZE; i++)
		pr_debug("%02x ", vha->node_name[i]);
	pr_debug("\n");
	pr_debug("qla2xxx HW vha->port_name: ");
	for (i = 0; i < WWN_SIZE; i++)
		pr_debug("%02x ", vha->port_name[i]);
	pr_debug("\n");

	pr_debug("qla2xxx passed configfs WWPN: ");
	put_unaligned_be64(wwpn, b);
	for (i = 0; i < WWN_SIZE; i++)
		pr_debug("%02x ", b[i]);
	pr_debug("\n");
}