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
struct gfs2_sbd {int /*<<< orphan*/  sd_jbsize; } ;
struct gfs2_meta_header {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; int /*<<< orphan*/  i_eattr; int /*<<< orphan*/  i_inode; } ;
struct gfs2_ea_header {int /*<<< orphan*/  ea_flags; int /*<<< orphan*/  ea_type; int /*<<< orphan*/  ea_rec_len; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_EAFLAG_LAST ; 
 int /*<<< orphan*/  GFS2_EATYPE_UNUSED ; 
 struct gfs2_ea_header* GFS2_EA_BH2FIRST (struct buffer_head*) ; 
 int /*<<< orphan*/  GFS2_FORMAT_EA ; 
 int /*<<< orphan*/  GFS2_METATYPE_EA ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_buffer_clear_tail (struct buffer_head*,int) ; 
 struct buffer_head* gfs2_meta_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_metatype_set (struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 

__attribute__((used)) static void gfs2_init_xattr(struct gfs2_inode *ip)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct buffer_head *bh;
	struct gfs2_ea_header *ea;

	bh = gfs2_meta_new(ip->i_gl, ip->i_eattr);
	gfs2_trans_add_meta(ip->i_gl, bh);
	gfs2_metatype_set(bh, GFS2_METATYPE_EA, GFS2_FORMAT_EA);
	gfs2_buffer_clear_tail(bh, sizeof(struct gfs2_meta_header));

	ea = GFS2_EA_BH2FIRST(bh);
	ea->ea_rec_len = cpu_to_be32(sdp->sd_jbsize);
	ea->ea_type = GFS2_EATYPE_UNUSED;
	ea->ea_flags = GFS2_EAFLAG_LAST;

	brelse(bh);
}