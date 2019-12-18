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
typedef  int /*<<< orphan*/  atomic_long_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,long) ; 

__attribute__((used)) static inline void smc_wr_tx_set_wr_id(atomic_long_t *wr_tx_id, long val)
{
	atomic_long_set(wr_tx_id, val);
}