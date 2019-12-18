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
struct qstr {unsigned char* name; int len; } ;
struct inode {unsigned long i_size; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {unsigned long b_size; scalar_t__ b_data; } ;
struct bfs_dirent {int /*<<< orphan*/  name; int /*<<< orphan*/  ino; } ;
struct TYPE_2__ {scalar_t__ i_sblock; } ;

/* Variables and functions */
 unsigned long BFS_BSIZE ; 
 scalar_t__ BFS_DIRENT_SIZE ; 
 TYPE_1__* BFS_I (struct inode*) ; 
 int BFS_NAMELEN ; 
 scalar_t__ bfs_namecmp (int,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct buffer_head *bfs_find_entry(struct inode *dir,
			const struct qstr *child,
			struct bfs_dirent **res_dir)
{
	unsigned long block = 0, offset = 0;
	struct buffer_head *bh = NULL;
	struct bfs_dirent *de;
	const unsigned char *name = child->name;
	int namelen = child->len;

	*res_dir = NULL;
	if (namelen > BFS_NAMELEN)
		return NULL;

	while (block * BFS_BSIZE + offset < dir->i_size) {
		if (!bh) {
			bh = sb_bread(dir->i_sb, BFS_I(dir)->i_sblock + block);
			if (!bh) {
				block++;
				continue;
			}
		}
		de = (struct bfs_dirent *)(bh->b_data + offset);
		offset += BFS_DIRENT_SIZE;
		if (le16_to_cpu(de->ino) &&
				bfs_namecmp(namelen, name, de->name)) {
			*res_dir = de;
			return bh;
		}
		if (offset < bh->b_size)
			continue;
		brelse(bh);
		bh = NULL;
		offset = 0;
		block++;
	}
	brelse(bh);
	return NULL;
}