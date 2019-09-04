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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct completion {int dummy; } ;
struct ath10k_sdio_irq_enable_regs {int dummy; } ;
struct ath10k_sdio_irq_data {int /*<<< orphan*/  mtx; struct ath10k_sdio_irq_enable_regs* irq_en_reg; } ;
struct ath10k_sdio {int /*<<< orphan*/  func; int /*<<< orphan*/  wr_async_work; int /*<<< orphan*/  workqueue; struct ath10k_sdio_irq_data irq_data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBOX_INT_STATUS_ENABLE_ADDRESS ; 
 int /*<<< orphan*/  SDIO_IRQ_DISABLE_TIMEOUT_HZ ; 
 int ath10k_sdio_prep_async_req (struct ath10k*,int /*<<< orphan*/ ,struct sk_buff*,struct completion*,int,int /*<<< orphan*/ ) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ath10k_sdio_irq_enable_regs*,int) ; 
 int /*<<< orphan*/  memset (struct ath10k_sdio_irq_enable_regs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int sdio_release_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_sdio_irq_disable(struct ath10k *ar)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	struct ath10k_sdio_irq_data *irq_data = &ar_sdio->irq_data;
	struct ath10k_sdio_irq_enable_regs *regs = irq_data->irq_en_reg;
	struct sk_buff *skb;
	struct completion irqs_disabled_comp;
	int ret;

	skb = dev_alloc_skb(sizeof(*regs));
	if (!skb)
		return;

	mutex_lock(&irq_data->mtx);

	memset(regs, 0, sizeof(*regs)); /* disable all interrupts */
	memcpy(skb->data, regs, sizeof(*regs));
	skb_put(skb, sizeof(*regs));

	mutex_unlock(&irq_data->mtx);

	init_completion(&irqs_disabled_comp);
	ret = ath10k_sdio_prep_async_req(ar, MBOX_INT_STATUS_ENABLE_ADDRESS,
					 skb, &irqs_disabled_comp, false, 0);
	if (ret)
		goto out;

	queue_work(ar_sdio->workqueue, &ar_sdio->wr_async_work);

	/* Wait for the completion of the IRQ disable request.
	 * If there is a timeout we will try to disable irq's anyway.
	 */
	ret = wait_for_completion_timeout(&irqs_disabled_comp,
					  SDIO_IRQ_DISABLE_TIMEOUT_HZ);
	if (!ret)
		ath10k_warn(ar, "sdio irq disable request timed out\n");

	sdio_claim_host(ar_sdio->func);

	ret = sdio_release_irq(ar_sdio->func);
	if (ret)
		ath10k_warn(ar, "failed to release sdio interrupt: %d\n", ret);

	sdio_release_host(ar_sdio->func);

out:
	kfree_skb(skb);
}