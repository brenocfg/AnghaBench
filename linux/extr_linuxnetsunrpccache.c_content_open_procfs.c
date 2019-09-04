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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct cache_detail {int dummy; } ;

/* Variables and functions */
 struct cache_detail* PDE_DATA (struct inode*) ; 
 int content_open (struct inode*,struct file*,struct cache_detail*) ; 

__attribute__((used)) static int content_open_procfs(struct inode *inode, struct file *filp)
{
	struct cache_detail *cd = PDE_DATA(inode);

	return content_open(inode, filp, cd);
}