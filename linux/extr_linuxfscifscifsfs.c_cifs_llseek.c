#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_mapping; } ;
struct file {int dummy; } ;
typedef  int loff_t ;
struct TYPE_6__ {scalar_t__ time; } ;
struct TYPE_5__ {scalar_t__ nrpages; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_CACHE_READ (TYPE_3__*) ; 
 TYPE_3__* CIFS_I (struct inode*) ; 
 int SEEK_CUR ; 
 int SEEK_SET ; 
 int cifs_revalidate_file_attr (struct file*) ; 
 struct inode* file_inode (struct file*) ; 
 int filemap_fdatawait (TYPE_1__*) ; 
 int generic_file_llseek (struct file*,int,int) ; 
 int /*<<< orphan*/  mapping_set_error (TYPE_1__*,int) ; 

__attribute__((used)) static loff_t cifs_llseek(struct file *file, loff_t offset, int whence)
{
	/*
	 * whence == SEEK_END || SEEK_DATA || SEEK_HOLE => we must revalidate
	 * the cached file length
	 */
	if (whence != SEEK_SET && whence != SEEK_CUR) {
		int rc;
		struct inode *inode = file_inode(file);

		/*
		 * We need to be sure that all dirty pages are written and the
		 * server has the newest file length.
		 */
		if (!CIFS_CACHE_READ(CIFS_I(inode)) && inode->i_mapping &&
		    inode->i_mapping->nrpages != 0) {
			rc = filemap_fdatawait(inode->i_mapping);
			if (rc) {
				mapping_set_error(inode->i_mapping, rc);
				return rc;
			}
		}
		/*
		 * Some applications poll for the file length in this strange
		 * way so we must seek to end on non-oplocked files by
		 * setting the revalidate time to zero.
		 */
		CIFS_I(inode)->time = 0;

		rc = cifs_revalidate_file_attr(file);
		if (rc < 0)
			return (loff_t)rc;
	}
	return generic_file_llseek(file, offset, whence);
}