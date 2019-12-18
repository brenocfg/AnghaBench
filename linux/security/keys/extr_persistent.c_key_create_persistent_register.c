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
struct user_namespace {struct key* persistent_keyring_register; } ;
struct key {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_ALLOC_NOT_IN_QUOTA ; 
 int KEY_POS_ALL ; 
 int KEY_POS_SETATTR ; 
 int KEY_USR_READ ; 
 int KEY_USR_VIEW ; 
 int /*<<< orphan*/  KGIDT_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KUIDT_INIT (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  current_cred () ; 
 struct key* keyring_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int key_create_persistent_register(struct user_namespace *ns)
{
	struct key *reg = keyring_alloc(".persistent_register",
					KUIDT_INIT(0), KGIDT_INIT(0),
					current_cred(),
					((KEY_POS_ALL & ~KEY_POS_SETATTR) |
					 KEY_USR_VIEW | KEY_USR_READ),
					KEY_ALLOC_NOT_IN_QUOTA, NULL, NULL);
	if (IS_ERR(reg))
		return PTR_ERR(reg);

	ns->persistent_keyring_register = reg;
	return 0;
}