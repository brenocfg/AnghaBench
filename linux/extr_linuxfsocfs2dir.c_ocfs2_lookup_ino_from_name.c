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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_dir_lookup_result {int /*<<< orphan*/ * member_0; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ocfs2_find_files_on_disk (char const*,int,int /*<<< orphan*/ *,struct inode*,struct ocfs2_dir_lookup_result*) ; 
 int /*<<< orphan*/  ocfs2_free_dir_lookup_result (struct ocfs2_dir_lookup_result*) ; 

int ocfs2_lookup_ino_from_name(struct inode *dir, const char *name,
			       int namelen, u64 *blkno)
{
	int ret;
	struct ocfs2_dir_lookup_result lookup = { NULL, };

	ret = ocfs2_find_files_on_disk(name, namelen, blkno, dir, &lookup);
	ocfs2_free_dir_lookup_result(&lookup);

	return ret;
}