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
struct inode {int i_size; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int OMFS_DIR_START ; 
 struct buffer_head* omfs_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int omfs_hash (char const*,int,int) ; 

__attribute__((used)) static struct buffer_head *omfs_get_bucket(struct inode *dir,
		const char *name, int namelen, int *ofs)
{
	int nbuckets = (dir->i_size - OMFS_DIR_START)/8;
	int bucket = omfs_hash(name, namelen, nbuckets);

	*ofs = OMFS_DIR_START + bucket * 8;
	return omfs_bread(dir->i_sb, dir->i_ino);
}