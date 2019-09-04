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
struct ath6kl {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_STATE_ON ; 
 int __ath6kl_init_hw_start (struct ath6kl*) ; 

int ath6kl_init_hw_start(struct ath6kl *ar)
{
	int err;

	err = __ath6kl_init_hw_start(ar);
	if (err)
		return err;
	ar->state = ATH6KL_STATE_ON;
	return 0;
}