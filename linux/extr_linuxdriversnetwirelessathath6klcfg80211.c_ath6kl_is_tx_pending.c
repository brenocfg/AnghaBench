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
struct ath6kl {scalar_t__* tx_pending; int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 size_t ath6kl_wmi_get_control_ep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ath6kl_is_tx_pending(struct ath6kl *ar)
{
	return ar->tx_pending[ath6kl_wmi_get_control_ep(ar->wmi)] == 0;
}