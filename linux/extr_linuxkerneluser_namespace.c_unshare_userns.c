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
struct cred {int dummy; } ;

/* Variables and functions */
 unsigned long CLONE_NEWUSER ; 
 int ENOMEM ; 
 int create_user_ns (struct cred*) ; 
 struct cred* prepare_creds () ; 
 int /*<<< orphan*/  put_cred (struct cred*) ; 

int unshare_userns(unsigned long unshare_flags, struct cred **new_cred)
{
	struct cred *cred;
	int err = -ENOMEM;

	if (!(unshare_flags & CLONE_NEWUSER))
		return 0;

	cred = prepare_creds();
	if (cred) {
		err = create_user_ns(cred);
		if (err)
			put_cred(cred);
		else
			*new_cred = cred;
	}

	return err;
}