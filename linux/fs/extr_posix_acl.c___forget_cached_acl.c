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
 int /*<<< orphan*/  is_uncached_acl (struct posix_acl*) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 struct posix_acl* xchg (struct posix_acl**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __forget_cached_acl(struct posix_acl **p)
{
	struct posix_acl *old;

	old = xchg(p, ACL_NOT_CACHED);
	if (!is_uncached_acl(old))
		posix_acl_release(old);
}