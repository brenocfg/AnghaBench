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
struct file {struct aa_revision* private_data; } ;
struct aa_revision {int /*<<< orphan*/  ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_put_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct aa_revision*) ; 

__attribute__((used)) static int ns_revision_release(struct inode *inode, struct file *file)
{
	struct aa_revision *rev = file->private_data;

	if (rev) {
		aa_put_ns(rev->ns);
		kfree(rev);
	}

	return 0;
}