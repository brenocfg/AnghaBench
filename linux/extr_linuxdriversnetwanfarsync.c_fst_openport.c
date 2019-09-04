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
struct fst_port_info {int run; size_t index; scalar_t__ hwif; scalar_t__ txqs; scalar_t__ txqe; TYPE_1__* card; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_OPEN ; 
 int FST_RDL (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ FST_RUNNING ; 
 int IPSTS_DCD ; 
 int IPSTS_INDICATE ; 
 int OPSTS_DTR ; 
 int OPSTS_RTS ; 
 int /*<<< orphan*/  STARTPORT ; 
 int /*<<< orphan*/  STOPPORT ; 
 scalar_t__ X21 ; 
 scalar_t__ X21D ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fst_issue_cmd (struct fst_port_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fst_op_raise (struct fst_port_info*,int) ; 
 int /*<<< orphan*/  fst_rx_config (struct fst_port_info*) ; 
 int /*<<< orphan*/  fst_tx_config (struct fst_port_info*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_to_dev (struct fst_port_info*) ; 
 int /*<<< orphan*/ * v24DebouncedSts ; 

__attribute__((used)) static void
fst_openport(struct fst_port_info *port)
{
	int signals;

	/* Only init things if card is actually running. This allows open to
	 * succeed for downloads etc.
	 */
	if (port->card->state == FST_RUNNING) {
		if (port->run) {
			dbg(DBG_OPEN, "open: found port already running\n");

			fst_issue_cmd(port, STOPPORT);
			port->run = 0;
		}

		fst_rx_config(port);
		fst_tx_config(port);
		fst_op_raise(port, OPSTS_RTS | OPSTS_DTR);

		fst_issue_cmd(port, STARTPORT);
		port->run = 1;

		signals = FST_RDL(port->card, v24DebouncedSts[port->index]);
		if (signals & (((port->hwif == X21) || (port->hwif == X21D))
			       ? IPSTS_INDICATE : IPSTS_DCD))
			netif_carrier_on(port_to_dev(port));
		else
			netif_carrier_off(port_to_dev(port));

		port->txqe = 0;
		port->txqs = 0;
	}

}