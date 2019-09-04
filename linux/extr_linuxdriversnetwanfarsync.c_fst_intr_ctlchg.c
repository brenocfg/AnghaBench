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
struct fst_port_info {size_t index; scalar_t__ hwif; } ;
struct fst_card_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_INTR ; 
 int FST_RDL (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 int IPSTS_DCD ; 
 int IPSTS_INDICATE ; 
 scalar_t__ X21 ; 
 scalar_t__ X21D ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_to_dev (struct fst_port_info*) ; 
 int /*<<< orphan*/ * v24DebouncedSts ; 

__attribute__((used)) static void
fst_intr_ctlchg(struct fst_card_info *card, struct fst_port_info *port)
{
	int signals;

	signals = FST_RDL(card, v24DebouncedSts[port->index]);

	if (signals & (((port->hwif == X21) || (port->hwif == X21D))
		       ? IPSTS_INDICATE : IPSTS_DCD)) {
		if (!netif_carrier_ok(port_to_dev(port))) {
			dbg(DBG_INTR, "DCD active\n");
			netif_carrier_on(port_to_dev(port));
		}
	} else {
		if (netif_carrier_ok(port_to_dev(port))) {
			dbg(DBG_INTR, "DCD lost\n");
			netif_carrier_off(port_to_dev(port));
		}
	}
}