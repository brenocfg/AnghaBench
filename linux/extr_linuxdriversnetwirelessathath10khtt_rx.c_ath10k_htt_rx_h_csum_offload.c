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
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_htt_rx_get_csum_state (struct sk_buff*) ; 

__attribute__((used)) static void ath10k_htt_rx_h_csum_offload(struct sk_buff *msdu)
{
	msdu->ip_summed = ath10k_htt_rx_get_csum_state(msdu);
}