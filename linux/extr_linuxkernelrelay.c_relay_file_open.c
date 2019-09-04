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
struct rchan_buf {int /*<<< orphan*/  kref; } ;
struct inode {struct rchan_buf* i_private; } ;
struct file {struct rchan_buf* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int nonseekable_open (struct inode*,struct file*) ; 

__attribute__((used)) static int relay_file_open(struct inode *inode, struct file *filp)
{
	struct rchan_buf *buf = inode->i_private;
	kref_get(&buf->kref);
	filp->private_data = buf;

	return nonseekable_open(inode, filp);
}