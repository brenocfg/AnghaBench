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
struct file {struct aa_revision* private_data; } ;
struct aa_revision {scalar_t__ ns; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ aa_get_current_ns () ; 
 scalar_t__ aa_get_ns (int /*<<< orphan*/ ) ; 
 struct aa_revision* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ns_revision_open(struct inode *inode, struct file *file)
{
	struct aa_revision *rev = kzalloc(sizeof(*rev), GFP_KERNEL);

	if (!rev)
		return -ENOMEM;

	rev->ns = aa_get_ns(inode->i_private);
	if (!rev->ns)
		rev->ns = aa_get_current_ns();
	file->private_data = rev;

	return 0;
}