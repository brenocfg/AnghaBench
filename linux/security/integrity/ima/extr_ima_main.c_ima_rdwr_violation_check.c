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
struct integrity_iint_cache {int /*<<< orphan*/  atomic_flags; } ;
struct inode {int /*<<< orphan*/  i_readcount; } ;
struct file {int f_mode; int /*<<< orphan*/  f_path; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  IMA_MUST_MEASURE ; 
 scalar_t__ IS_IMA (struct inode*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  ima_add_violation (struct file*,char const*,struct integrity_iint_cache*,char*,char*) ; 
 char* ima_d_path (int /*<<< orphan*/ *,char**,char*) ; 
 scalar_t__ inode_is_open_for_write (struct inode*) ; 
 struct integrity_iint_cache* integrity_iint_find (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ima_rdwr_violation_check(struct file *file,
				     struct integrity_iint_cache *iint,
				     int must_measure,
				     char **pathbuf,
				     const char **pathname,
				     char *filename)
{
	struct inode *inode = file_inode(file);
	fmode_t mode = file->f_mode;
	bool send_tomtou = false, send_writers = false;

	if (mode & FMODE_WRITE) {
		if (atomic_read(&inode->i_readcount) && IS_IMA(inode)) {
			if (!iint)
				iint = integrity_iint_find(inode);
			/* IMA_MEASURE is set from reader side */
			if (iint && test_bit(IMA_MUST_MEASURE,
						&iint->atomic_flags))
				send_tomtou = true;
		}
	} else {
		if (must_measure)
			set_bit(IMA_MUST_MEASURE, &iint->atomic_flags);
		if (inode_is_open_for_write(inode) && must_measure)
			send_writers = true;
	}

	if (!send_tomtou && !send_writers)
		return;

	*pathname = ima_d_path(&file->f_path, pathbuf, filename);

	if (send_tomtou)
		ima_add_violation(file, *pathname, iint,
				  "invalid_pcr", "ToMToU");
	if (send_writers)
		ima_add_violation(file, *pathname, iint,
				  "invalid_pcr", "open_writers");
}