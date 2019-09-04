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
typedef  scalar_t__ u8 ;
struct fst_port_info {int dummy; } ;
struct fst_card_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  alarmIndicationSignal; int /*<<< orphan*/  receiveRemoteAlarm; int /*<<< orphan*/  lossOfSignal; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_INTR ; 
 scalar_t__ FST_RDB (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_to_dev (struct fst_port_info*) ; 
 TYPE_1__ suStatus ; 

__attribute__((used)) static void
fst_intr_te1_alarm(struct fst_card_info *card, struct fst_port_info *port)
{
	u8 los;
	u8 rra;
	u8 ais;

	los = FST_RDB(card, suStatus.lossOfSignal);
	rra = FST_RDB(card, suStatus.receiveRemoteAlarm);
	ais = FST_RDB(card, suStatus.alarmIndicationSignal);

	if (los) {
		/*
		 * Lost the link
		 */
		if (netif_carrier_ok(port_to_dev(port))) {
			dbg(DBG_INTR, "Net carrier off\n");
			netif_carrier_off(port_to_dev(port));
		}
	} else {
		/*
		 * Link available
		 */
		if (!netif_carrier_ok(port_to_dev(port))) {
			dbg(DBG_INTR, "Net carrier on\n");
			netif_carrier_on(port_to_dev(port));
		}
	}

	if (los)
		dbg(DBG_INTR, "Assert LOS Alarm\n");
	else
		dbg(DBG_INTR, "De-assert LOS Alarm\n");
	if (rra)
		dbg(DBG_INTR, "Assert RRA Alarm\n");
	else
		dbg(DBG_INTR, "De-assert RRA Alarm\n");

	if (ais)
		dbg(DBG_INTR, "Assert AIS Alarm\n");
	else
		dbg(DBG_INTR, "De-assert AIS Alarm\n");
}