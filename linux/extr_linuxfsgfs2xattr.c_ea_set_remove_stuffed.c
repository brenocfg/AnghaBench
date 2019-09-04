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
typedef  scalar_t__ u32 ;
struct gfs2_inode {int /*<<< orphan*/  i_inode; int /*<<< orphan*/  i_gl; } ;
struct gfs2_ea_location {int /*<<< orphan*/  el_bh; struct gfs2_ea_header* el_prev; struct gfs2_ea_header* el_ea; } ;
struct gfs2_ea_header {int /*<<< orphan*/  ea_flags; int /*<<< orphan*/  ea_rec_len; int /*<<< orphan*/  ea_type; } ;

/* Variables and functions */
 struct gfs2_ea_header* GFS2_EA2NEXT (struct gfs2_ea_header*) ; 
 int /*<<< orphan*/  GFS2_EAFLAG_LAST ; 
 int /*<<< orphan*/  GFS2_EATYPE_UNUSED ; 
 scalar_t__ GFS2_EA_IS_LAST (struct gfs2_ea_header*) ; 
 int /*<<< orphan*/  GFS2_EA_IS_STUFFED (struct gfs2_ea_header*) ; 
 scalar_t__ GFS2_EA_REC_LEN (struct gfs2_ea_header*) ; 
 int /*<<< orphan*/  GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  gfs2_assert_withdraw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ea_set_remove_stuffed(struct gfs2_inode *ip,
				  struct gfs2_ea_location *el)
{
	struct gfs2_ea_header *ea = el->el_ea;
	struct gfs2_ea_header *prev = el->el_prev;
	u32 len;

	gfs2_trans_add_meta(ip->i_gl, el->el_bh);

	if (!prev || !GFS2_EA_IS_STUFFED(ea)) {
		ea->ea_type = GFS2_EATYPE_UNUSED;
		return;
	} else if (GFS2_EA2NEXT(prev) != ea) {
		prev = GFS2_EA2NEXT(prev);
		gfs2_assert_withdraw(GFS2_SB(&ip->i_inode), GFS2_EA2NEXT(prev) == ea);
	}

	len = GFS2_EA_REC_LEN(prev) + GFS2_EA_REC_LEN(ea);
	prev->ea_rec_len = cpu_to_be32(len);

	if (GFS2_EA_IS_LAST(ea))
		prev->ea_flags |= GFS2_EAFLAG_LAST;
}