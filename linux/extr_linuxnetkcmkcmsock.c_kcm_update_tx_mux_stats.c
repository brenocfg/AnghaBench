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
struct TYPE_4__ {scalar_t__ tx_bytes; scalar_t__ tx_msgs; } ;
struct kcm_psock {TYPE_2__ stats; scalar_t__ saved_tx_bytes; scalar_t__ saved_tx_msgs; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_msgs; int /*<<< orphan*/  tx_bytes; } ;
struct kcm_mux {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCM_STATS_ADD (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void kcm_update_tx_mux_stats(struct kcm_mux *mux,
				    struct kcm_psock *psock)
{
	KCM_STATS_ADD(mux->stats.tx_bytes,
		      psock->stats.tx_bytes - psock->saved_tx_bytes);
	mux->stats.tx_msgs +=
		psock->stats.tx_msgs - psock->saved_tx_msgs;
	psock->saved_tx_msgs = psock->stats.tx_msgs;
	psock->saved_tx_bytes = psock->stats.tx_bytes;
}