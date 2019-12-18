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
struct file {int dummy; } ;
struct dir_context {int dummy; } ;

/* Variables and functions */
 int __fat_readdir (int /*<<< orphan*/ ,struct file*,struct dir_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 

__attribute__((used)) static int fat_readdir(struct file *file, struct dir_context *ctx)
{
	return __fat_readdir(file_inode(file), file, ctx, 0, NULL);
}