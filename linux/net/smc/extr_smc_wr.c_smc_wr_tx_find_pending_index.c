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
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct smc_link {size_t wr_tx_cnt; TYPE_1__* wr_tx_pends; } ;
struct TYPE_2__ {scalar_t__ wr_id; } ;

/* Variables and functions */

__attribute__((used)) static inline int smc_wr_tx_find_pending_index(struct smc_link *link, u64 wr_id)
{
	u32 i;

	for (i = 0; i < link->wr_tx_cnt; i++) {
		if (link->wr_tx_pends[i].wr_id == wr_id)
			return i;
	}
	return link->wr_tx_cnt;
}