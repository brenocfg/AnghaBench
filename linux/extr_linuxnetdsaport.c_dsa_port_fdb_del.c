#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct dsa_port {int /*<<< orphan*/  index; TYPE_1__* ds; } ;
struct dsa_notifier_fdb_info {unsigned char const* addr; int /*<<< orphan*/  vid; int /*<<< orphan*/  port; int /*<<< orphan*/  sw_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_NOTIFIER_FDB_DEL ; 
 int dsa_port_notify (struct dsa_port*,int /*<<< orphan*/ ,struct dsa_notifier_fdb_info*) ; 

int dsa_port_fdb_del(struct dsa_port *dp, const unsigned char *addr,
		     u16 vid)
{
	struct dsa_notifier_fdb_info info = {
		.sw_index = dp->ds->index,
		.port = dp->index,
		.addr = addr,
		.vid = vid,

	};

	return dsa_port_notify(dp, DSA_NOTIFIER_FDB_DEL, &info);
}