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
struct ath10k_tpc_stats_final {int dummy; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ath10k_tpc_stats_final*) ; 

__attribute__((used)) static inline void
ath10k_debug_tpc_stats_final_process(struct ath10k *ar,
				     struct ath10k_tpc_stats_final *tpc_stats)
{
	kfree(tpc_stats);
}