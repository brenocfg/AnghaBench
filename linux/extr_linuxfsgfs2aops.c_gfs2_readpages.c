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
struct list_head {int dummy; } ;
struct inode {int dummy; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_flags; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  SDF_SHUTDOWN ; 
 int /*<<< orphan*/  gfs2_block_map ; 
 int /*<<< orphan*/  gfs2_glock_dq (struct gfs2_holder*) ; 
 int gfs2_glock_nq (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_uninit (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_is_stuffed (struct gfs2_inode*) ; 
 int mpage_readpages (struct address_space*,struct list_head*,unsigned int,int /*<<< orphan*/ ) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int gfs2_readpages(struct file *file, struct address_space *mapping,
			  struct list_head *pages, unsigned nr_pages)
{
	struct inode *inode = mapping->host;
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_holder gh;
	int ret;

	gfs2_holder_init(ip->i_gl, LM_ST_SHARED, 0, &gh);
	ret = gfs2_glock_nq(&gh);
	if (unlikely(ret))
		goto out_uninit;
	if (!gfs2_is_stuffed(ip))
		ret = mpage_readpages(mapping, pages, nr_pages, gfs2_block_map);
	gfs2_glock_dq(&gh);
out_uninit:
	gfs2_holder_uninit(&gh);
	if (unlikely(test_bit(SDF_SHUTDOWN, &sdp->sd_flags)))
		ret = -EIO;
	return ret;
}