#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bytes; scalar_t__ msgs; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;
struct kcm_psock {TYPE_2__ strp; scalar_t__ saved_rx_bytes; scalar_t__ saved_rx_msgs; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_msgs; int /*<<< orphan*/  rx_bytes; } ;
struct kcm_mux {TYPE_3__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRP_STATS_ADD (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void kcm_update_rx_mux_stats(struct kcm_mux *mux,
				    struct kcm_psock *psock)
{
	STRP_STATS_ADD(mux->stats.rx_bytes,
		       psock->strp.stats.bytes -
		       psock->saved_rx_bytes);
	mux->stats.rx_msgs +=
		psock->strp.stats.msgs - psock->saved_rx_msgs;
	psock->saved_rx_msgs = psock->strp.stats.msgs;
	psock->saved_rx_bytes = psock->strp.stats.bytes;
}