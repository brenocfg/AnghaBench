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
struct ath6kl_sdio {int /*<<< orphan*/  func; int /*<<< orphan*/  irq_wq; int /*<<< orphan*/  irq_handling; } ;
struct ath6kl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_err (char*,int) ; 
 int /*<<< orphan*/  ath6kl_sdio_is_on_irq (struct ath6kl*) ; 
 struct ath6kl_sdio* ath6kl_sdio_priv (struct ath6kl*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int sdio_release_irq (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath6kl_sdio_irq_disable(struct ath6kl *ar)
{
	struct ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	int ret;

	sdio_claim_host(ar_sdio->func);

	if (atomic_read(&ar_sdio->irq_handling)) {
		sdio_release_host(ar_sdio->func);

		ret = wait_event_interruptible(ar_sdio->irq_wq,
					       ath6kl_sdio_is_on_irq(ar));
		if (ret)
			return;

		sdio_claim_host(ar_sdio->func);
	}

	ret = sdio_release_irq(ar_sdio->func);
	if (ret)
		ath6kl_err("Failed to release sdio irq: %d\n", ret);

	sdio_release_host(ar_sdio->func);
}