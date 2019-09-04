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
 int /*<<< orphan*/  dcookie_exit () ; 
 int /*<<< orphan*/  dcookie_mutex ; 
 int /*<<< orphan*/  is_live () ; 
 int /*<<< orphan*/  kfree (struct dcookie_user*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void dcookie_unregister(struct dcookie_user * user)
{
	mutex_lock(&dcookie_mutex);

	list_del(&user->next);
	kfree(user);

	if (!is_live())
		dcookie_exit();

	mutex_unlock(&dcookie_mutex);
}