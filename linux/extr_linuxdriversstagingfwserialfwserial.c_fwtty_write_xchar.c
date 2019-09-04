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
struct TYPE_2__ {int /*<<< orphan*/  xchars; } ;
struct fwtty_port {int /*<<< orphan*/  peer; TYPE_1__ stats; } ;
struct fwtty_peer {int /*<<< orphan*/  fifo_addr; } ;
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int /*<<< orphan*/  TCODE_WRITE_BLOCK_REQUEST ; 
 int /*<<< orphan*/  fwtty_dbg (struct fwtty_port*,char*,char) ; 
 int /*<<< orphan*/  fwtty_send_data_async (struct fwtty_peer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,struct fwtty_port*) ; 
 struct fwtty_peer* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void fwtty_write_xchar(struct fwtty_port *port, char ch)
{
	struct fwtty_peer *peer;

	++port->stats.xchars;

	fwtty_dbg(port, "%02x\n", ch);

	rcu_read_lock();
	peer = rcu_dereference(port->peer);
	if (peer) {
		fwtty_send_data_async(peer, TCODE_WRITE_BLOCK_REQUEST,
				      peer->fifo_addr, &ch, sizeof(ch),
				      NULL, port);
	}
	rcu_read_unlock();
}