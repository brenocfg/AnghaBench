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
struct user_namespace {int /*<<< orphan*/  keyring_name_list; } ;
struct key {char* description; int /*<<< orphan*/  name_link; } ;

/* Variables and functions */
 struct user_namespace* current_user_ns () ; 
 int /*<<< orphan*/  keyring_name_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void keyring_publish_name(struct key *keyring)
{
	struct user_namespace *ns = current_user_ns();

	if (keyring->description &&
	    keyring->description[0] &&
	    keyring->description[0] != '.') {
		write_lock(&keyring_name_lock);
		list_add_tail(&keyring->name_link, &ns->keyring_name_list);
		write_unlock(&keyring_name_lock);
	}
}