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
struct smbd_connection {int new_credits_offered; int /*<<< orphan*/  lock_new_credits_offered; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int manage_credits_prior_sending(struct smbd_connection *info)
{
	int new_credits;

	spin_lock(&info->lock_new_credits_offered);
	new_credits = info->new_credits_offered;
	info->new_credits_offered = 0;
	spin_unlock(&info->lock_new_credits_offered);

	return new_credits;
}