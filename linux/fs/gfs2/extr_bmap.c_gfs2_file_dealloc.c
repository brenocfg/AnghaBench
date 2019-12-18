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
struct gfs2_inode {int dummy; } ;

/* Variables and functions */
 int punch_hole (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int gfs2_file_dealloc(struct gfs2_inode *ip)
{
	return punch_hole(ip, 0, 0);
}