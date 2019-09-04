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
struct posix_acl_entry {int dummy; } ;
struct posix_acl {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct posix_acl* kmalloc (size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_acl_init (struct posix_acl*,int) ; 

struct posix_acl *
posix_acl_alloc(int count, gfp_t flags)
{
	const size_t size = sizeof(struct posix_acl) +
	                    count * sizeof(struct posix_acl_entry);
	struct posix_acl *acl = kmalloc(size, flags);
	if (acl)
		posix_acl_init(acl, count);
	return acl;
}