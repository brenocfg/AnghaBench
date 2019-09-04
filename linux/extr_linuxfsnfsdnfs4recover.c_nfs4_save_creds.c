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
struct cred {int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 struct cred* override_creds (struct cred*) ; 
 struct cred* prepare_creds () ; 
 int /*<<< orphan*/  put_cred (struct cred*) ; 

__attribute__((used)) static int
nfs4_save_creds(const struct cred **original_creds)
{
	struct cred *new;

	new = prepare_creds();
	if (!new)
		return -ENOMEM;

	new->fsuid = GLOBAL_ROOT_UID;
	new->fsgid = GLOBAL_ROOT_GID;
	*original_creds = override_creds(new);
	put_cred(new);
	return 0;
}