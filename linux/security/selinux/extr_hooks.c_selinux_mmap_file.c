#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
struct TYPE_3__ {struct file* file; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {scalar_t__ checkreqprot; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE__MAP ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_FILE ; 
 unsigned long MAP_SHARED ; 
 unsigned long MAP_TYPE ; 
 int /*<<< orphan*/  current_cred () ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int file_map_prot_check (struct file*,unsigned long,int) ; 
 int inode_has_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 TYPE_2__ selinux_state ; 

__attribute__((used)) static int selinux_mmap_file(struct file *file, unsigned long reqprot,
			     unsigned long prot, unsigned long flags)
{
	struct common_audit_data ad;
	int rc;

	if (file) {
		ad.type = LSM_AUDIT_DATA_FILE;
		ad.u.file = file;
		rc = inode_has_perm(current_cred(), file_inode(file),
				    FILE__MAP, &ad);
		if (rc)
			return rc;
	}

	if (selinux_state.checkreqprot)
		prot = reqprot;

	return file_map_prot_check(file, prot,
				   (flags & MAP_TYPE) == MAP_SHARED);
}