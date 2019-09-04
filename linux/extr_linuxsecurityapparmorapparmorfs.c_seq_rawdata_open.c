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
struct seq_file {scalar_t__ private; } ;
struct inode {int /*<<< orphan*/  i_private; } ;
struct file {scalar_t__ private_data; } ;
struct aa_loaddata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int ENOENT ; 
 struct aa_loaddata* __aa_get_loaddata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_loaddata (struct aa_loaddata*) ; 
 int single_open (struct file*,int (*) (struct seq_file*,void*),struct aa_loaddata*) ; 

__attribute__((used)) static int seq_rawdata_open(struct inode *inode, struct file *file,
			    int (*show)(struct seq_file *, void *))
{
	struct aa_loaddata *data = __aa_get_loaddata(inode->i_private);
	int error;

	if (!data)
		/* lost race this ent is being reaped */
		return -ENOENT;

	error = single_open(file, show, data);
	if (error) {
		AA_BUG(file->private_data &&
		       ((struct seq_file *)file->private_data)->private);
		aa_put_loaddata(data);
	}

	return error;
}