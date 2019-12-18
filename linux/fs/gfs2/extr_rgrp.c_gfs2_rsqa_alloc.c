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
 int gfs2_qa_alloc (struct gfs2_inode*) ; 

int gfs2_rsqa_alloc(struct gfs2_inode *ip)
{
	return gfs2_qa_alloc(ip);
}