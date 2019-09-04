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
struct v9fs_inode {int /*<<< orphan*/  qid; } ;
struct p9_stat_dotl {int /*<<< orphan*/  st_gen; int /*<<< orphan*/  qid; } ;
struct inode {int /*<<< orphan*/  i_generation; } ;

/* Variables and functions */
 struct v9fs_inode* V9FS_I (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int v9fs_set_inode_dotl(struct inode *inode,  void *data)
{
	struct v9fs_inode *v9inode = V9FS_I(inode);
	struct p9_stat_dotl *st = (struct p9_stat_dotl *)data;

	memcpy(&v9inode->qid, &st->qid, sizeof(st->qid));
	inode->i_generation = st->st_gen;
	return 0;
}