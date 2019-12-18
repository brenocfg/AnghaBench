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
struct inode {int /*<<< orphan*/  i_private; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOENT ; 
 int /*<<< orphan*/  __aa_get_loaddata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policy_view_capable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rawdata_open(struct inode *inode, struct file *file)
{
	if (!policy_view_capable(NULL))
		return -EACCES;
	file->private_data = __aa_get_loaddata(inode->i_private);
	if (!file->private_data)
		/* lost race: this entry is being reaped */
		return -ENOENT;

	return 0;
}