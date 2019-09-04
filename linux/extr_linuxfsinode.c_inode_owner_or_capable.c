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
struct user_namespace {int dummy; } ;
struct inode {int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FOWNER ; 
 int /*<<< orphan*/  current_fsuid () ; 
 struct user_namespace* current_user_ns () ; 
 scalar_t__ kuid_has_mapping (struct user_namespace*,int /*<<< orphan*/ ) ; 
 scalar_t__ ns_capable (struct user_namespace*,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool inode_owner_or_capable(const struct inode *inode)
{
	struct user_namespace *ns;

	if (uid_eq(current_fsuid(), inode->i_uid))
		return true;

	ns = current_user_ns();
	if (kuid_has_mapping(ns, inode->i_uid) && ns_capable(ns, CAP_FOWNER))
		return true;
	return false;
}