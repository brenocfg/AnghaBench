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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_2__ {unsigned int sb_bsize; } ;
struct gfs2_sbd {TYPE_1__ sd_sb; int /*<<< orphan*/  sd_jbsize; } ;
struct gfs2_meta_header {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; int /*<<< orphan*/  i_inode; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DIO_WAIT ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFS2_METATYPE_JD ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int do_div (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gfs2_assert_warn (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int gfs2_dir_read_stuffed (struct gfs2_inode*,int /*<<< orphan*/ *,unsigned int) ; 
 int gfs2_extent_map (int /*<<< orphan*/ *,scalar_t__,int*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  gfs2_is_jdata (struct gfs2_inode*) ; 
 scalar_t__ gfs2_is_stuffed (struct gfs2_inode*) ; 
 struct buffer_head* gfs2_meta_ra (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int gfs2_meta_read (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int gfs2_metatype_check (struct gfs2_sbd*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 

__attribute__((used)) static int gfs2_dir_read_data(struct gfs2_inode *ip, __be64 *buf,
			      unsigned int size)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	u64 lblock, dblock;
	u32 extlen = 0;
	unsigned int o;
	int copied = 0;
	int error = 0;

	if (gfs2_is_stuffed(ip))
		return gfs2_dir_read_stuffed(ip, buf, size);

	if (gfs2_assert_warn(sdp, gfs2_is_jdata(ip)))
		return -EINVAL;

	lblock = 0;
	o = do_div(lblock, sdp->sd_jbsize) + sizeof(struct gfs2_meta_header);

	while (copied < size) {
		unsigned int amount;
		struct buffer_head *bh;
		int new;

		amount = size - copied;
		if (amount > sdp->sd_sb.sb_bsize - o)
			amount = sdp->sd_sb.sb_bsize - o;

		if (!extlen) {
			new = 0;
			error = gfs2_extent_map(&ip->i_inode, lblock, &new,
						&dblock, &extlen);
			if (error || !dblock)
				goto fail;
			BUG_ON(extlen < 1);
			bh = gfs2_meta_ra(ip->i_gl, dblock, extlen);
		} else {
			error = gfs2_meta_read(ip->i_gl, dblock, DIO_WAIT, 0, &bh);
			if (error)
				goto fail;
		}
		error = gfs2_metatype_check(sdp, bh, GFS2_METATYPE_JD);
		if (error) {
			brelse(bh);
			goto fail;
		}
		dblock++;
		extlen--;
		memcpy(buf, bh->b_data + o, amount);
		brelse(bh);
		buf += (amount/sizeof(__be64));
		copied += amount;
		lblock++;
		o = sizeof(struct gfs2_meta_header);
	}

	return copied;
fail:
	return (copied) ? copied : error;
}