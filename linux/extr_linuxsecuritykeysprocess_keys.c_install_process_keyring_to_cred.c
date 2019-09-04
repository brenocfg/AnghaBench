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
struct key {int dummy; } ;
struct cred {struct key* process_keyring; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_ALLOC_QUOTA_OVERRUN ; 
 int KEY_POS_ALL ; 
 int KEY_USR_VIEW ; 
 int PTR_ERR (struct key*) ; 
 struct key* keyring_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int install_process_keyring_to_cred(struct cred *new)
{
	struct key *keyring;

	if (new->process_keyring)
		return 0;

	keyring = keyring_alloc("_pid", new->uid, new->gid, new,
				KEY_POS_ALL | KEY_USR_VIEW,
				KEY_ALLOC_QUOTA_OVERRUN,
				NULL, NULL);
	if (IS_ERR(keyring))
		return PTR_ERR(keyring);

	new->process_keyring = keyring;
	return 0;
}