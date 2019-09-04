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
struct key_user {int /*<<< orphan*/  node; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  key_user_lock ; 
 int /*<<< orphan*/  key_user_tree ; 
 int /*<<< orphan*/  kfree (struct key_user*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void key_user_put(struct key_user *user)
{
	if (refcount_dec_and_lock(&user->usage, &key_user_lock)) {
		rb_erase(&user->node, &key_user_tree);
		spin_unlock(&key_user_lock);

		kfree(user);
	}
}