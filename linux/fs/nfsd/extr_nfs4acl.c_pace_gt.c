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
struct posix_acl_entry {scalar_t__ e_tag; int /*<<< orphan*/  e_gid; int /*<<< orphan*/  e_uid; } ;

/* Variables and functions */
 scalar_t__ ACL_GROUP ; 
 scalar_t__ ACL_USER ; 
 int gid_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uid_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
pace_gt(struct posix_acl_entry *pace1, struct posix_acl_entry *pace2)
{
	if (pace1->e_tag != pace2->e_tag)
		return pace1->e_tag > pace2->e_tag;
	if (pace1->e_tag == ACL_USER)
		return uid_gt(pace1->e_uid, pace2->e_uid);
	if (pace1->e_tag == ACL_GROUP)
		return gid_gt(pace1->e_gid, pace2->e_gid);
	return false;
}