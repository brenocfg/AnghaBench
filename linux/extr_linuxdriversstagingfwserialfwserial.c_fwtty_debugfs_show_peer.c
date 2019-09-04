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
struct seq_file {int dummy; } ;
struct fwtty_peer {int generation; scalar_t__ status_addr; scalar_t__ mgmt_addr; scalar_t__ guid; int /*<<< orphan*/  max_payload; int /*<<< orphan*/  speed; int /*<<< orphan*/  node_id; TYPE_1__* unit; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 unsigned long long dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static void fwtty_debugfs_show_peer(struct seq_file *m, struct fwtty_peer *peer)
{
	int generation = peer->generation;

	smp_rmb();
	seq_printf(m, " %s:", dev_name(&peer->unit->device));
	seq_printf(m, " node:%04x gen:%d", peer->node_id, generation);
	seq_printf(m, " sp:%d max:%d guid:%016llx", peer->speed,
		   peer->max_payload, (unsigned long long)peer->guid);
	seq_printf(m, " mgmt:%012llx", (unsigned long long)peer->mgmt_addr);
	seq_printf(m, " addr:%012llx", (unsigned long long)peer->status_addr);
	seq_putc(m, '\n');
}