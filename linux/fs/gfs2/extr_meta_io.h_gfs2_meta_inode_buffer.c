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
struct gfs2_inode {int /*<<< orphan*/  i_no_addr; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int gfs2_meta_indirect_buffer (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 

__attribute__((used)) static inline int gfs2_meta_inode_buffer(struct gfs2_inode *ip,
					 struct buffer_head **bhp)
{
	return gfs2_meta_indirect_buffer(ip, 0, ip->i_no_addr, bhp);
}