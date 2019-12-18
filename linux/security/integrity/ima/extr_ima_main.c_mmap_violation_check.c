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
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/  f_path; int /*<<< orphan*/  f_mapping; } ;
typedef  enum ima_hooks { ____Placeholder_ima_hooks } ima_hooks ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_INTEGRITY_DATA ; 
 int ETXTBSY ; 
 int MMAP_CHECK ; 
 struct inode* file_inode (struct file*) ; 
 char* ima_d_path (int /*<<< orphan*/ *,char**,char*) ; 
 int /*<<< orphan*/  integrity_audit_msg (int /*<<< orphan*/ ,struct inode*,char const*,char*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mapping_writably_mapped (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmap_violation_check(enum ima_hooks func, struct file *file,
				char **pathbuf, const char **pathname,
				char *filename)
{
	struct inode *inode;
	int rc = 0;

	if ((func == MMAP_CHECK) && mapping_writably_mapped(file->f_mapping)) {
		rc = -ETXTBSY;
		inode = file_inode(file);

		if (!*pathbuf)	/* ima_rdwr_violation possibly pre-fetched */
			*pathname = ima_d_path(&file->f_path, pathbuf,
					       filename);
		integrity_audit_msg(AUDIT_INTEGRITY_DATA, inode, *pathname,
				    "mmap_file", "mmapped_writers", rc, 0);
	}
	return rc;
}