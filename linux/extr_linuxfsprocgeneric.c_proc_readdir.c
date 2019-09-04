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
struct dir_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDE (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 int proc_readdir_de (struct file*,struct dir_context*,int /*<<< orphan*/ ) ; 

int proc_readdir(struct file *file, struct dir_context *ctx)
{
	struct inode *inode = file_inode(file);

	return proc_readdir_de(file, ctx, PDE(inode));
}