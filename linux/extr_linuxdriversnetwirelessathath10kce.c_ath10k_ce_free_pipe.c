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
struct ath10k_ce_pipe {TYPE_1__* ops; } ;
struct ath10k_ce {struct ath10k_ce_pipe* ce_states; } ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ce_free_pipe ) (struct ath10k*,int) ;} ;

/* Variables and functions */
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 int /*<<< orphan*/  stub1 (struct ath10k*,int) ; 

void ath10k_ce_free_pipe(struct ath10k *ar, int ce_id)
{
	struct ath10k_ce *ce = ath10k_ce_priv(ar);
	struct ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];

	ce_state->ops->ce_free_pipe(ar, ce_id);
}