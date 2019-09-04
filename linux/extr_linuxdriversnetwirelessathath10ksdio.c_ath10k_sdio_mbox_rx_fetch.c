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
struct ath10k_sdio {int n_rx_pkts; int /*<<< orphan*/ * rx_pkts; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_sdio_mbox_free_rx_pkt (int /*<<< orphan*/ *) ; 
 int ath10k_sdio_mbox_rx_packet (struct ath10k*,int /*<<< orphan*/ *) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 

__attribute__((used)) static int ath10k_sdio_mbox_rx_fetch(struct ath10k *ar)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	int ret, i;

	for (i = 0; i < ar_sdio->n_rx_pkts; i++) {
		ret = ath10k_sdio_mbox_rx_packet(ar,
						 &ar_sdio->rx_pkts[i]);
		if (ret)
			goto err;
	}

	return 0;

err:
	/* Free all packets that was not successfully fetched. */
	for (; i < ar_sdio->n_rx_pkts; i++)
		ath10k_sdio_mbox_free_rx_pkt(&ar_sdio->rx_pkts[i]);

	return ret;
}