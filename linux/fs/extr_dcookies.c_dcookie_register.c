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
struct dcookie_user {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ dcookie_init () ; 
 int /*<<< orphan*/  dcookie_mutex ; 
 int /*<<< orphan*/  dcookie_users ; 
 int /*<<< orphan*/  is_live () ; 
 int /*<<< orphan*/  kfree (struct dcookie_user*) ; 
 struct dcookie_user* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct dcookie_user * dcookie_register(void)
{
	struct dcookie_user * user;

	mutex_lock(&dcookie_mutex);

	user = kmalloc(sizeof(struct dcookie_user), GFP_KERNEL);
	if (!user)
		goto out;

	if (!is_live() && dcookie_init())
		goto out_free;

	list_add(&user->next, &dcookie_users);

out:
	mutex_unlock(&dcookie_mutex);
	return user;
out_free:
	kfree(user);
	user = NULL;
	goto out;
}