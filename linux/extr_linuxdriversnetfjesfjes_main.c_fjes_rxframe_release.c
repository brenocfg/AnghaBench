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
struct TYPE_4__ {TYPE_1__* ep_shm_info; } ;
struct fjes_adapter {TYPE_2__ hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  fjes_hw_epbuf_rx_curpkt_drop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fjes_rxframe_release(struct fjes_adapter *adapter, int cur_epid)
{
	fjes_hw_epbuf_rx_curpkt_drop(&adapter->hw.ep_shm_info[cur_epid].rx);
}