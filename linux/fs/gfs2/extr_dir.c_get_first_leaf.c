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
typedef  int /*<<< orphan*/  u32 ;
struct gfs2_inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int get_leaf (struct gfs2_inode*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int get_leaf_nr (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_first_leaf(struct gfs2_inode *dip, u32 index,
			  struct buffer_head **bh_out)
{
	u64 leaf_no;
	int error;

	error = get_leaf_nr(dip, index, &leaf_no);
	if (!error)
		error = get_leaf(dip, leaf_no, bh_out);

	return error;
}