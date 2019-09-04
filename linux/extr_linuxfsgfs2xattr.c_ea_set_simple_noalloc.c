#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  i_ctime; } ;
struct gfs2_inode {TYPE_1__ i_inode; int /*<<< orphan*/  i_gl; } ;
struct gfs2_ea_request {int dummy; } ;
struct gfs2_ea_header {int dummy; } ;
struct ea_set {scalar_t__ es_el; scalar_t__ ea_split; struct gfs2_ea_request* es_er; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_SB (TYPE_1__*) ; 
 int /*<<< orphan*/  I_DIRTY_DATASYNC ; 
 scalar_t__ RES_DINODE ; 
 int RES_EATTR ; 
 int /*<<< orphan*/  __mark_inode_dirty (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (TYPE_1__*) ; 
 int /*<<< orphan*/  ea_set_remove_stuffed (struct gfs2_inode*,scalar_t__) ; 
 struct gfs2_ea_header* ea_split_ea (struct gfs2_ea_header*) ; 
 int /*<<< orphan*/  ea_write (struct gfs2_inode*,struct gfs2_ea_header*,struct gfs2_ea_request*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_trans_begin (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ea_set_simple_noalloc(struct gfs2_inode *ip, struct buffer_head *bh,
				 struct gfs2_ea_header *ea, struct ea_set *es)
{
	struct gfs2_ea_request *er = es->es_er;
	int error;

	error = gfs2_trans_begin(GFS2_SB(&ip->i_inode), RES_DINODE + 2 * RES_EATTR, 0);
	if (error)
		return error;

	gfs2_trans_add_meta(ip->i_gl, bh);

	if (es->ea_split)
		ea = ea_split_ea(ea);

	ea_write(ip, ea, er);

	if (es->es_el)
		ea_set_remove_stuffed(ip, es->es_el);

	ip->i_inode.i_ctime = current_time(&ip->i_inode);
	__mark_inode_dirty(&ip->i_inode, I_DIRTY_DATASYNC);

	gfs2_trans_end(GFS2_SB(&ip->i_inode));
	return error;
}