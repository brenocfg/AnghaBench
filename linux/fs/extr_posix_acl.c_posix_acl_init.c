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
struct posix_acl {int a_count; int /*<<< orphan*/  a_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

void
posix_acl_init(struct posix_acl *acl, int count)
{
	refcount_set(&acl->a_refcount, 1);
	acl->a_count = count;
}