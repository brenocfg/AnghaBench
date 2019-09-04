#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct file {int dummy; } ;
struct cred {int dummy; } ;
struct TYPE_2__ {struct file* file; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_AUDIT_DATA_FILE ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int inode_has_perm (struct cred const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 

__attribute__((used)) static inline int file_path_has_perm(const struct cred *cred,
				     struct file *file,
				     u32 av)
{
	struct common_audit_data ad;

	ad.type = LSM_AUDIT_DATA_FILE;
	ad.u.file = file;
	return inode_has_perm(cred, file_inode(file), av, &ad);
}