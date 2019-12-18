#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct address_space* i_mapping; int /*<<< orphan*/  i_mode; } ;
struct gfs2_inode {TYPE_2__ i_inode; int /*<<< orphan*/  i_flags; } ;
struct TYPE_6__ {TYPE_3__* ln_sbd; } ;
struct gfs2_glock {TYPE_1__ gl_name; int /*<<< orphan*/  gl_ail_count; } ;
struct address_space {int dummy; } ;
struct TYPE_8__ {scalar_t__ sd_rindex_uptodate; int /*<<< orphan*/  sd_rindex; } ;

/* Variables and functions */
 int DIO_METADATA ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int GFS2_LFC_INODE_GO_INVAL ; 
 int GFS2_LOG_HEAD_FLUSH_NORMAL ; 
 int /*<<< orphan*/  GIF_INVALID ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  forget_all_cached_acls (TYPE_2__*) ; 
 int /*<<< orphan*/  gfs2_assert_withdraw (TYPE_3__*,int) ; 
 int /*<<< orphan*/  gfs2_clear_glop_pending (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_dir_hash_inval (struct gfs2_inode*) ; 
 struct address_space* gfs2_glock2aspace (struct gfs2_glock*) ; 
 struct gfs2_inode* gfs2_glock2inode (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_log_flush (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  security_inode_invalidate_secctx (TYPE_2__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_inode_pages (struct address_space*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inode_go_inval(struct gfs2_glock *gl, int flags)
{
	struct gfs2_inode *ip = gfs2_glock2inode(gl);

	gfs2_assert_withdraw(gl->gl_name.ln_sbd, !atomic_read(&gl->gl_ail_count));

	if (flags & DIO_METADATA) {
		struct address_space *mapping = gfs2_glock2aspace(gl);
		truncate_inode_pages(mapping, 0);
		if (ip) {
			set_bit(GIF_INVALID, &ip->i_flags);
			forget_all_cached_acls(&ip->i_inode);
			security_inode_invalidate_secctx(&ip->i_inode);
			gfs2_dir_hash_inval(ip);
		}
	}

	if (ip == GFS2_I(gl->gl_name.ln_sbd->sd_rindex)) {
		gfs2_log_flush(gl->gl_name.ln_sbd, NULL,
			       GFS2_LOG_HEAD_FLUSH_NORMAL |
			       GFS2_LFC_INODE_GO_INVAL);
		gl->gl_name.ln_sbd->sd_rindex_uptodate = 0;
	}
	if (ip && S_ISREG(ip->i_inode.i_mode))
		truncate_inode_pages(ip->i_inode.i_mapping, 0);

	gfs2_clear_glop_pending(ip);
}