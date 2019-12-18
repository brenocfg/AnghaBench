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
typedef  int u32 ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct gfs2_inode {int i_diskflags; int /*<<< orphan*/ * i_hash_cache; struct inode i_inode; int /*<<< orphan*/  i_depth; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * ERR_PTR (int) ; 
 int GFP_NOFS ; 
 int GFS2_DIF_EXHASH ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/ * __vmalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_consist_inode (struct gfs2_inode*) ; 
 int gfs2_dir_read_data (struct gfs2_inode*,int /*<<< orphan*/ *,int) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/ * kmalloc (int,int) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be64 *gfs2_dir_get_hash_table(struct gfs2_inode *ip)
{
	struct inode *inode = &ip->i_inode;
	int ret;
	u32 hsize;
	__be64 *hc;

	BUG_ON(!(ip->i_diskflags & GFS2_DIF_EXHASH));

	hc = ip->i_hash_cache;
	if (hc)
		return hc;

	hsize = BIT(ip->i_depth);
	hsize *= sizeof(__be64);
	if (hsize != i_size_read(&ip->i_inode)) {
		gfs2_consist_inode(ip);
		return ERR_PTR(-EIO);
	}

	hc = kmalloc(hsize, GFP_NOFS | __GFP_NOWARN);
	if (hc == NULL)
		hc = __vmalloc(hsize, GFP_NOFS, PAGE_KERNEL);

	if (hc == NULL)
		return ERR_PTR(-ENOMEM);

	ret = gfs2_dir_read_data(ip, hc, hsize);
	if (ret < 0) {
		kvfree(hc);
		return ERR_PTR(ret);
	}

	spin_lock(&inode->i_lock);
	if (likely(!ip->i_hash_cache)) {
		ip->i_hash_cache = hc;
		hc = NULL;
	}
	spin_unlock(&inode->i_lock);
	kvfree(hc);

	return ip->i_hash_cache;
}