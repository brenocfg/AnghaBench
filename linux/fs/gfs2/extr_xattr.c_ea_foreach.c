#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct gfs2_meta_header {int dummy; } ;
struct gfs2_inode {int i_diskflags; int /*<<< orphan*/  i_gl; int /*<<< orphan*/  i_inode; int /*<<< orphan*/  i_eattr; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  ea_call_t ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_3__ {int sd_inptrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIO_WAIT ; 
 int EIO ; 
 int GFS2_DIF_EA_INDIRECT ; 
 int /*<<< orphan*/  GFS2_METATYPE_IN ; 
 TYPE_1__* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int ea_foreach_i (struct gfs2_inode*,struct buffer_head*,int /*<<< orphan*/ ,void*) ; 
 int gfs2_meta_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 scalar_t__ gfs2_metatype_check (TYPE_1__*,struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ea_foreach(struct gfs2_inode *ip, ea_call_t ea_call, void *data)
{
	struct buffer_head *bh, *eabh;
	__be64 *eablk, *end;
	int error;

	error = gfs2_meta_read(ip->i_gl, ip->i_eattr, DIO_WAIT, 0, &bh);
	if (error)
		return error;

	if (!(ip->i_diskflags & GFS2_DIF_EA_INDIRECT)) {
		error = ea_foreach_i(ip, bh, ea_call, data);
		goto out;
	}

	if (gfs2_metatype_check(GFS2_SB(&ip->i_inode), bh, GFS2_METATYPE_IN)) {
		error = -EIO;
		goto out;
	}

	eablk = (__be64 *)(bh->b_data + sizeof(struct gfs2_meta_header));
	end = eablk + GFS2_SB(&ip->i_inode)->sd_inptrs;

	for (; eablk < end; eablk++) {
		u64 bn;

		if (!*eablk)
			break;
		bn = be64_to_cpu(*eablk);

		error = gfs2_meta_read(ip->i_gl, bn, DIO_WAIT, 0, &eabh);
		if (error)
			break;
		error = ea_foreach_i(ip, eabh, ea_call, data);
		brelse(eabh);
		if (error)
			break;
	}
out:
	brelse(bh);
	return error;
}