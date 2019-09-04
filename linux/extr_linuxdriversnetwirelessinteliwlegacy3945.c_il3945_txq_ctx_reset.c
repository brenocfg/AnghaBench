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
struct il_priv {TYPE_1__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  IL_ERR (char*,int) ; 
 int /*<<< orphan*/  il3945_hw_txq_ctx_free (struct il_priv*) ; 
 int il3945_tx_reset (struct il_priv*) ; 
 int il_alloc_txq_mem (struct il_priv*) ; 
 int il_tx_queue_init (struct il_priv*,int) ; 

__attribute__((used)) static int
il3945_txq_ctx_reset(struct il_priv *il)
{
	int rc, txq_id;

	il3945_hw_txq_ctx_free(il);

	/* allocate tx queue structure */
	rc = il_alloc_txq_mem(il);
	if (rc)
		return rc;

	/* Tx CMD queue */
	rc = il3945_tx_reset(il);
	if (rc)
		goto error;

	/* Tx queue(s) */
	for (txq_id = 0; txq_id < il->hw_params.max_txq_num; txq_id++) {
		rc = il_tx_queue_init(il, txq_id);
		if (rc) {
			IL_ERR("Tx %d queue init failed\n", txq_id);
			goto error;
		}
	}

	return rc;

error:
	il3945_hw_txq_ctx_free(il);
	return rc;
}