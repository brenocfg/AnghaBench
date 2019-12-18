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
typedef  int /*<<< orphan*/  u32 ;
struct task_security_struct {int /*<<< orphan*/  sid; } ;
struct superblock_security_struct {int /*<<< orphan*/  sid; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILESYSTEM__ASSOCIATE ; 
 int /*<<< orphan*/  FILESYSTEM__RELABELFROM ; 
 int /*<<< orphan*/  SECCLASS_FILESYSTEM ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct task_security_struct* selinux_cred (struct cred const*) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int may_context_mount_inode_relabel(u32 sid,
			struct superblock_security_struct *sbsec,
			const struct cred *cred)
{
	const struct task_security_struct *tsec = selinux_cred(cred);
	int rc;
	rc = avc_has_perm(&selinux_state,
			  tsec->sid, sbsec->sid, SECCLASS_FILESYSTEM,
			  FILESYSTEM__RELABELFROM, NULL);
	if (rc)
		return rc;

	rc = avc_has_perm(&selinux_state,
			  sid, sbsec->sid, SECCLASS_FILESYSTEM,
			  FILESYSTEM__ASSOCIATE, NULL);
	return rc;
}