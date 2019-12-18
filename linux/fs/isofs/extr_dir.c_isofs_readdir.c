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
struct iso_directory_record {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct dir_context {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int do_isofs_readdir (struct inode*,struct file*,struct dir_context*,char*,struct iso_directory_record*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static int isofs_readdir(struct file *file, struct dir_context *ctx)
{
	int result;
	char *tmpname;
	struct iso_directory_record *tmpde;
	struct inode *inode = file_inode(file);

	tmpname = (char *)__get_free_page(GFP_KERNEL);
	if (tmpname == NULL)
		return -ENOMEM;

	tmpde = (struct iso_directory_record *) (tmpname+1024);

	result = do_isofs_readdir(inode, file, ctx, tmpname, tmpde);

	free_page((unsigned long) tmpname);
	return result;
}