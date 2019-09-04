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
struct ath5k_hw {int rx_pending; int /*<<< orphan*/  rxtq; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath5k_schedule_rx(struct ath5k_hw *ah)
{
	ah->rx_pending = true;
	tasklet_schedule(&ah->rxtq);
}