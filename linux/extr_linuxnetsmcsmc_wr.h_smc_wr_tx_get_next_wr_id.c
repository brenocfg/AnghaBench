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
struct smc_link {int /*<<< orphan*/  wr_tx_id; } ;

/* Variables and functions */
 long atomic_long_inc_return (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline long smc_wr_tx_get_next_wr_id(struct smc_link *link)
{
	return atomic_long_inc_return(&link->wr_tx_id);
}