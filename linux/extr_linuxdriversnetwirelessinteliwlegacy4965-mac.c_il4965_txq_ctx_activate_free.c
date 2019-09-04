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
struct TYPE_2__ {int max_txq_num; } ;
struct il_priv {int /*<<< orphan*/  txq_ctx_active_msk; TYPE_1__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
il4965_txq_ctx_activate_free(struct il_priv *il)
{
	int txq_id;

	for (txq_id = 0; txq_id < il->hw_params.max_txq_num; txq_id++)
		if (!test_and_set_bit(txq_id, &il->txq_ctx_active_msk))
			return txq_id;
	return -1;
}