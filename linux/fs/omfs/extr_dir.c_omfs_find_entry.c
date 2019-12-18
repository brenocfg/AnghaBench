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
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/ * b_data; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct buffer_head* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct buffer_head* omfs_get_bucket (struct inode*,char const*,int,int*) ; 
 struct buffer_head* omfs_scan_list (struct inode*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct buffer_head *omfs_find_entry(struct inode *dir,
					   const char *name, int namelen)
{
	struct buffer_head *bh;
	int ofs;
	u64 block, dummy;

	bh = omfs_get_bucket(dir, name, namelen, &ofs);
	if (!bh)
		return ERR_PTR(-EIO);

	block = be64_to_cpu(*((__be64 *) &bh->b_data[ofs]));
	brelse(bh);

	return omfs_scan_list(dir, block, name, namelen, &dummy);
}