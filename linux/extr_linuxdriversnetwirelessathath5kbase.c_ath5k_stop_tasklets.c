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
struct ath5k_hw {int rx_pending; int tx_pending; int /*<<< orphan*/  ani_tasklet; int /*<<< orphan*/  beacontq; int /*<<< orphan*/  txtq; int /*<<< orphan*/  rxtq; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath5k_stop_tasklets(struct ath5k_hw *ah)
{
	ah->rx_pending = false;
	ah->tx_pending = false;
	tasklet_kill(&ah->rxtq);
	tasklet_kill(&ah->txtq);
	tasklet_kill(&ah->beacontq);
	tasklet_kill(&ah->ani_tasklet);
}