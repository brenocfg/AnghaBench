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
struct il_priv {int /*<<< orphan*/  txq_ctx_active_msk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
il_txq_ctx_deactivate(struct il_priv *il, int txq_id)
{
	clear_bit(txq_id, &il->txq_ctx_active_msk);
}