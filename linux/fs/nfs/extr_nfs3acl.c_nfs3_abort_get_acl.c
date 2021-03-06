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
 int /*<<< orphan*/  ACL_NOT_CACHED ; 
 int /*<<< orphan*/  cmpxchg (struct posix_acl**,struct posix_acl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 struct posix_acl* uncached_acl_sentinel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs3_abort_get_acl(struct posix_acl **p)
{
	struct posix_acl *sentinel = uncached_acl_sentinel(current);

	/* Remove our sentinel upon failure. */
	cmpxchg(p, sentinel, ACL_NOT_CACHED);
}