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
typedef  int /*<<< orphan*/  umode_t ;
struct posix_acl {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct posix_acl* posix_acl_clone (struct posix_acl*,int /*<<< orphan*/ ) ; 
 int posix_acl_create_masq (struct posix_acl*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 

int
__posix_acl_create(struct posix_acl **acl, gfp_t gfp, umode_t *mode_p)
{
	struct posix_acl *clone = posix_acl_clone(*acl, gfp);
	int err = -ENOMEM;
	if (clone) {
		err = posix_acl_create_masq(clone, mode_p);
		if (err < 0) {
			posix_acl_release(clone);
			clone = NULL;
		}
	}
	posix_acl_release(*acl);
	*acl = clone;
	return err;
}