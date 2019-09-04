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
typedef  scalar_t__ u16 ;
struct ath10k_sdio_rx_data {TYPE_1__* skb; } ;
struct ath10k_htc_hdr {scalar_t__ trailer_len; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ __le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_trailer_only_msg(struct ath10k_sdio_rx_data *pkt)
{
	bool trailer_only = false;
	struct ath10k_htc_hdr *htc_hdr =
		(struct ath10k_htc_hdr *)pkt->skb->data;
	u16 len = __le16_to_cpu(htc_hdr->len);

	if (len == htc_hdr->trailer_len)
		trailer_only = true;

	return trailer_only;
}