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
struct posix_acl {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACL_NOT_CACHED ; 
 scalar_t__ cmpxchg (struct posix_acl**,scalar_t__,struct posix_acl*) ; 
 int /*<<< orphan*/  current ; 
 struct posix_acl* uncached_acl_sentinel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs3_prepare_get_acl(struct posix_acl **p)
{
	struct posix_acl *sentinel = uncached_acl_sentinel(current);

	if (cmpxchg(p, ACL_NOT_CACHED, sentinel) != ACL_NOT_CACHED) {
		/* Not the first reader or sentinel already in place. */
	}
}