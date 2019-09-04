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
struct fscache_objlist_data {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fscache_objlist_data* __seq_open_private (struct file*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fscache_objlist_config (struct fscache_objlist_data*) ; 
 int /*<<< orphan*/  fscache_objlist_ops ; 

__attribute__((used)) static int fscache_objlist_open(struct inode *inode, struct file *file)
{
	struct fscache_objlist_data *data;

	data = __seq_open_private(file, &fscache_objlist_ops, sizeof(*data));
	if (!data)
		return -ENOMEM;

	/* get the configuration key */
	fscache_objlist_config(data);

	return 0;
}