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
struct hif_scatter_req {int /*<<< orphan*/  list; } ;
struct ath6kl_sdio {int /*<<< orphan*/  scat_lock; int /*<<< orphan*/  scat_req; } ;
struct ath6kl {int dummy; } ;

/* Variables and functions */
 struct ath6kl_sdio* ath6kl_sdio_priv (struct ath6kl*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath6kl_sdio_scatter_req_add(struct ath6kl *ar,
					struct hif_scatter_req *s_req)
{
	struct ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);

	spin_lock_bh(&ar_sdio->scat_lock);

	list_add_tail(&s_req->list, &ar_sdio->scat_req);

	spin_unlock_bh(&ar_sdio->scat_lock);
}