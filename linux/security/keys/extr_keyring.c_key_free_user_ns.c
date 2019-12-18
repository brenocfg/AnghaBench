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
struct user_namespace {int /*<<< orphan*/  persistent_keyring_register; int /*<<< orphan*/  user_keyring_register; int /*<<< orphan*/  keyring_name_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keyring_name_lock ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void key_free_user_ns(struct user_namespace *ns)
{
	write_lock(&keyring_name_lock);
	list_del_init(&ns->keyring_name_list);
	write_unlock(&keyring_name_lock);

	key_put(ns->user_keyring_register);
#ifdef CONFIG_PERSISTENT_KEYRINGS
	key_put(ns->persistent_keyring_register);
#endif
}