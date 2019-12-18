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
struct gfs2_inode {int /*<<< orphan*/  i_rw_mutex; int /*<<< orphan*/  i_res; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_qa_delete (struct gfs2_inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_rs_deltree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void gfs2_rsqa_delete(struct gfs2_inode *ip, atomic_t *wcount)
{
	down_write(&ip->i_rw_mutex);
	if ((wcount == NULL) || (atomic_read(wcount) <= 1))
		gfs2_rs_deltree(&ip->i_res);
	up_write(&ip->i_rw_mutex);
	gfs2_qa_delete(ip, wcount);
}