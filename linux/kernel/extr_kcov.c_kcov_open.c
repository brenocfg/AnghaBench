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
struct kcov {int /*<<< orphan*/  lock; int /*<<< orphan*/  refcount; int /*<<< orphan*/  mode; } ;
struct inode {int dummy; } ;
struct file {struct kcov* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KCOV_MODE_DISABLED ; 
 struct kcov* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kcov_open(struct inode *inode, struct file *filep)
{
	struct kcov *kcov;

	kcov = kzalloc(sizeof(*kcov), GFP_KERNEL);
	if (!kcov)
		return -ENOMEM;
	kcov->mode = KCOV_MODE_DISABLED;
	refcount_set(&kcov->refcount, 1);
	spin_lock_init(&kcov->lock);
	filep->private_data = kcov;
	return nonseekable_open(inode, filep);
}