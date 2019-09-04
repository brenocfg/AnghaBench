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
typedef  int /*<<< orphan*/  u8 ;
struct ath10k {int dummy; } ;
typedef  enum ath10k_pkt_rx_err { ____Placeholder_ath10k_pkt_rx_err } ath10k_pkt_rx_err ;

/* Variables and functions */

__attribute__((used)) static inline
void ath10k_sta_update_rx_tid_stats(struct ath10k *ar, u8 *first_hdr,
				    unsigned long int num_msdus,
				    enum ath10k_pkt_rx_err err,
				    unsigned long int unchain_cnt,
				    unsigned long int drop_cnt,
				    unsigned long int drop_cnt_filter,
				    unsigned long int queued_msdus)
{
}