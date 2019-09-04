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
struct il_missed_beacon_notif {int /*<<< orphan*/  num_expected_beacons; int /*<<< orphan*/  num_recvd_beacons; int /*<<< orphan*/  total_missed_becons; int /*<<< orphan*/  consecutive_missed_beacons; } ;
struct TYPE_2__ {struct il_missed_beacon_notif missed_beacon; } ;
struct il_rx_pkt {TYPE_1__ u; } ;
struct il_rx_buf {int dummy; } ;
struct il_priv {scalar_t__ missed_beacon_threshold; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CALIB (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  S_SCANNING ; 
 int /*<<< orphan*/  il4965_init_sensitivity (struct il_priv*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il4965_hdl_missed_beacon(struct il_priv *il, struct il_rx_buf *rxb)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct il_missed_beacon_notif *missed_beacon;

	missed_beacon = &pkt->u.missed_beacon;
	if (le32_to_cpu(missed_beacon->consecutive_missed_beacons) >
	    il->missed_beacon_threshold) {
		D_CALIB("missed bcn cnsq %d totl %d rcd %d expctd %d\n",
			le32_to_cpu(missed_beacon->consecutive_missed_beacons),
			le32_to_cpu(missed_beacon->total_missed_becons),
			le32_to_cpu(missed_beacon->num_recvd_beacons),
			le32_to_cpu(missed_beacon->num_expected_beacons));
		if (!test_bit(S_SCANNING, &il->status))
			il4965_init_sensitivity(il);
	}
}