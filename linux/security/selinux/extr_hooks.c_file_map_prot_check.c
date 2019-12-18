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
struct file {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE__EXECUTE ; 
 int /*<<< orphan*/  FILE__READ ; 
 int /*<<< orphan*/  FILE__WRITE ; 
 scalar_t__ IS_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCESS__EXECMEM ; 
 unsigned long PROT_EXEC ; 
 unsigned long PROT_WRITE ; 
 int /*<<< orphan*/  SECCLASS_PROCESS ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cred_sid (struct cred const*) ; 
 struct cred* current_cred () ; 
 scalar_t__ default_noexec ; 
 int file_has_perm (struct cred const*,struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int file_map_prot_check(struct file *file, unsigned long prot, int shared)
{
	const struct cred *cred = current_cred();
	u32 sid = cred_sid(cred);
	int rc = 0;

	if (default_noexec &&
	    (prot & PROT_EXEC) && (!file || IS_PRIVATE(file_inode(file)) ||
				   (!shared && (prot & PROT_WRITE)))) {
		/*
		 * We are making executable an anonymous mapping or a
		 * private file mapping that will also be writable.
		 * This has an additional check.
		 */
		rc = avc_has_perm(&selinux_state,
				  sid, sid, SECCLASS_PROCESS,
				  PROCESS__EXECMEM, NULL);
		if (rc)
			goto error;
	}

	if (file) {
		/* read access is always possible with a mapping */
		u32 av = FILE__READ;

		/* write access only matters if the mapping is shared */
		if (shared && (prot & PROT_WRITE))
			av |= FILE__WRITE;

		if (prot & PROT_EXEC)
			av |= FILE__EXECUTE;

		return file_has_perm(cred, file, av);
	}

error:
	return rc;
}