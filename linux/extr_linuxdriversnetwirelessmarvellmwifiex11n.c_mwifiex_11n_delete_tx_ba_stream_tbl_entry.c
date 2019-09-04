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
struct mwifiex_tx_ba_stream_tbl {int /*<<< orphan*/  list; } ;
struct mwifiex_private {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  kfree (struct mwifiex_tx_ba_stream_tbl*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mwifiex_tx_ba_stream_tbl*) ; 
 scalar_t__ mwifiex_is_tx_ba_stream_ptr_valid (struct mwifiex_private*,struct mwifiex_tx_ba_stream_tbl*) ; 

void mwifiex_11n_delete_tx_ba_stream_tbl_entry(struct mwifiex_private *priv,
				struct mwifiex_tx_ba_stream_tbl *tx_ba_tsr_tbl)
{
	if (!tx_ba_tsr_tbl &&
	    mwifiex_is_tx_ba_stream_ptr_valid(priv, tx_ba_tsr_tbl))
		return;

	mwifiex_dbg(priv->adapter, INFO,
		    "info: tx_ba_tsr_tbl %p\n", tx_ba_tsr_tbl);

	list_del(&tx_ba_tsr_tbl->list);

	kfree(tx_ba_tsr_tbl);
}