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
struct ath6kl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_cfg80211_destroy (struct ath6kl*) ; 

void ath6kl_core_destroy(struct ath6kl *ar)
{
	ath6kl_cfg80211_destroy(ar);
}