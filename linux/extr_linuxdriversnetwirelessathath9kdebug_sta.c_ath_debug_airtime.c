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
typedef  scalar_t__ u32 ;
struct ath_softc {int dummy; } ;
struct ath_airtime_stats {int /*<<< orphan*/  tx_airtime; int /*<<< orphan*/  rx_airtime; } ;
struct ath_node {struct ath_airtime_stats airtime_stats; } ;

/* Variables and functions */

void ath_debug_airtime(struct ath_softc *sc,
		struct ath_node *an,
		u32 rx,
		u32 tx)
{
	struct ath_airtime_stats *astats = &an->airtime_stats;

	astats->rx_airtime += rx;
	astats->tx_airtime += tx;
}