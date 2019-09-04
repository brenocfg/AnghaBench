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
struct fwtty_transaction {int /*<<< orphan*/  (* callback ) (struct fw_card*,int,void*,size_t,struct fwtty_transaction*) ;struct fwtty_port* port; } ;
struct fwtty_port {int dummy; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int RCODE_COMPLETE ; 
 int /*<<< orphan*/  fwtty_log_tx_error (struct fwtty_port*,int) ; 
 int /*<<< orphan*/  fwtty_txn_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fwtty_transaction*) ; 
 int /*<<< orphan*/  stub1 (struct fw_card*,int,void*,size_t,struct fwtty_transaction*) ; 

__attribute__((used)) static void fwtty_common_callback(struct fw_card *card, int rcode,
				  void *payload, size_t len, void *cb_data)
{
	struct fwtty_transaction *txn = cb_data;
	struct fwtty_port *port = txn->port;

	if (port && rcode != RCODE_COMPLETE)
		fwtty_log_tx_error(port, rcode);
	if (txn->callback)
		txn->callback(card, rcode, payload, len, txn);
	kmem_cache_free(fwtty_txn_cache, txn);
}