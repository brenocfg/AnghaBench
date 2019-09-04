#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stats {scalar_t__ xchars; } ;
struct seq_file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  brk; int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; int /*<<< orphan*/  cts; int /*<<< orphan*/  rx; scalar_t__ tx; } ;
struct TYPE_7__ {int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {scalar_t__ console; } ;
struct fwtty_port {TYPE_4__ icount; TYPE_3__ rx_handler; int /*<<< orphan*/  con_data; TYPE_2__* fwcon_ops; TYPE_1__ port; int /*<<< orphan*/  stats; } ;
typedef  int /*<<< orphan*/  stats ;
struct TYPE_6__ {int /*<<< orphan*/  (* stats ) (struct stats*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct stats*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stub1 (struct stats*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fwtty_proc_show_port(struct seq_file *m, struct fwtty_port *port)
{
	struct stats stats;

	memcpy(&stats, &port->stats, sizeof(stats));
	if (port->port.console)
		(*port->fwcon_ops->stats)(&stats, port->con_data);

	seq_printf(m, " addr:%012llx tx:%d rx:%d", port->rx_handler.offset,
		   port->icount.tx + stats.xchars, port->icount.rx);
	seq_printf(m, " cts:%d dsr:%d rng:%d dcd:%d", port->icount.cts,
		   port->icount.dsr, port->icount.rng, port->icount.dcd);
	seq_printf(m, " fe:%d oe:%d pe:%d brk:%d", port->icount.frame,
		   port->icount.overrun, port->icount.parity, port->icount.brk);
}