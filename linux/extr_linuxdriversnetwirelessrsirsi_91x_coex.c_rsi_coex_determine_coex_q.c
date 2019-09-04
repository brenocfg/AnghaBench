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
struct rsi_coex_ctrl_block {int /*<<< orphan*/ * coex_tx_qs; } ;
typedef  enum rsi_coex_queues { ____Placeholder_rsi_coex_queues } rsi_coex_queues ;

/* Variables and functions */
 size_t RSI_COEX_Q_BT ; 
 size_t RSI_COEX_Q_COMMON ; 
 int RSI_COEX_Q_INVALID ; 
 size_t RSI_COEX_Q_WLAN ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum rsi_coex_queues rsi_coex_determine_coex_q
			(struct rsi_coex_ctrl_block *coex_cb)
{
	enum rsi_coex_queues q_num = RSI_COEX_Q_INVALID;

	if (skb_queue_len(&coex_cb->coex_tx_qs[RSI_COEX_Q_COMMON]) > 0)
		q_num = RSI_COEX_Q_COMMON;
	if (skb_queue_len(&coex_cb->coex_tx_qs[RSI_COEX_Q_BT]) > 0)
		q_num = RSI_COEX_Q_BT;
	if (skb_queue_len(&coex_cb->coex_tx_qs[RSI_COEX_Q_WLAN]) > 0)
		q_num = RSI_COEX_Q_WLAN;

	return q_num;
}