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
struct perf_peer {int /*<<< orphan*/  gidx; int /*<<< orphan*/  pidx; TYPE_1__* perf; } ;
struct TYPE_2__ {int /*<<< orphan*/  ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntb_peer_mw_clear_trans (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void perf_free_outbuf(struct perf_peer *peer)
{
	(void)ntb_peer_mw_clear_trans(peer->perf->ntb, peer->pidx, peer->gidx);
}