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
struct ath10k_htt {int /*<<< orphan*/  txdone_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_htt_tx_free_txdone_fifo(struct ath10k_htt *htt)
{
	WARN_ON(!kfifo_is_empty(&htt->txdone_fifo));
	kfifo_free(&htt->txdone_fifo);
}