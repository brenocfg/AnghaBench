#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rxstats; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;
struct ath_softc {TYPE_2__ debug; } ;
struct ath_rx_status {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_cmn_debug_stat_rx (int /*<<< orphan*/ *,struct ath_rx_status*) ; 

void ath_debug_stat_rx(struct ath_softc *sc, struct ath_rx_status *rs)
{
	ath9k_cmn_debug_stat_rx(&sc->debug.stats.rxstats, rs);
}