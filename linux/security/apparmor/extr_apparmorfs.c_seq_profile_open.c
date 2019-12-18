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
struct file {int /*<<< orphan*/ * private_data; } ;
struct aa_proxy {int dummy; } ;

/* Variables and functions */
 struct aa_proxy* aa_get_proxy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_proxy (struct aa_proxy*) ; 
 int single_open (struct file*,int (*) (struct seq_file*,void*),struct aa_proxy*) ; 

__attribute__((used)) static int seq_profile_open(struct inode *inode, struct file *file,
			    int (*show)(struct seq_file *, void *))
{
	struct aa_proxy *proxy = aa_get_proxy(inode->i_private);
	int error = single_open(file, show, proxy);

	if (error) {
		file->private_data = NULL;
		aa_put_proxy(proxy);
	}

	return error;
}