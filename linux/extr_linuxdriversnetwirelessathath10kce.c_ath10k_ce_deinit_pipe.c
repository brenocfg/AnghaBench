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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_ce_deinit_dest_ring (struct ath10k*,unsigned int) ; 
 int /*<<< orphan*/  ath10k_ce_deinit_src_ring (struct ath10k*,unsigned int) ; 

void ath10k_ce_deinit_pipe(struct ath10k *ar, unsigned int ce_id)
{
	ath10k_ce_deinit_src_ring(ar, ce_id);
	ath10k_ce_deinit_dest_ring(ar, ce_id);
}