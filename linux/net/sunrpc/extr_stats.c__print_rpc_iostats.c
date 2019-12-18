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
struct seq_file {int dummy; } ;
struct rpc_procinfo {int dummy; } ;
struct rpc_iostats {int /*<<< orphan*/  om_error_status; int /*<<< orphan*/  om_execute; int /*<<< orphan*/  om_rtt; int /*<<< orphan*/  om_queue; int /*<<< orphan*/  om_bytes_recv; int /*<<< orphan*/  om_bytes_sent; int /*<<< orphan*/  om_timeouts; int /*<<< orphan*/  om_ntrans; int /*<<< orphan*/  om_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  _print_name (struct seq_file*,int,struct rpc_procinfo const*) ; 
 int /*<<< orphan*/  ktime_to_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _print_rpc_iostats(struct seq_file *seq, struct rpc_iostats *stats,
			       int op, const struct rpc_procinfo *procs)
{
	_print_name(seq, op, procs);
	seq_printf(seq, "%lu %lu %lu %llu %llu %llu %llu %llu %lu\n",
		   stats->om_ops,
		   stats->om_ntrans,
		   stats->om_timeouts,
		   stats->om_bytes_sent,
		   stats->om_bytes_recv,
		   ktime_to_ms(stats->om_queue),
		   ktime_to_ms(stats->om_rtt),
		   ktime_to_ms(stats->om_execute),
		   stats->om_error_status);
}