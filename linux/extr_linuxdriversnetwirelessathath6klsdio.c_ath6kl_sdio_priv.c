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
struct ath6kl_sdio {int dummy; } ;
struct ath6kl {struct ath6kl_sdio* hif_priv; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ath6kl_sdio *ath6kl_sdio_priv(struct ath6kl *ar)
{
	return ar->hif_priv;
}