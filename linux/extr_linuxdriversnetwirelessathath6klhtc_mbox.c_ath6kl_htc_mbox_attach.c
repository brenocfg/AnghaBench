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
struct ath6kl {int /*<<< orphan*/ * htc_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_htc_mbox_ops ; 

void ath6kl_htc_mbox_attach(struct ath6kl *ar)
{
	ar->htc_ops = &ath6kl_htc_mbox_ops;
}