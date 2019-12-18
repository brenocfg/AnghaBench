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
struct ccid2_hc_tx_sock {scalar_t__ tx_pipe; scalar_t__ tx_cwnd; } ;

/* Variables and functions */

__attribute__((used)) static inline bool ccid2_cwnd_network_limited(struct ccid2_hc_tx_sock *hc)
{
	return hc->tx_pipe >= hc->tx_cwnd;
}