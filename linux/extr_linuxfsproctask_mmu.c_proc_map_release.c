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
struct seq_file {struct proc_maps_private* private; } ;
struct proc_maps_private {scalar_t__ mm; } ;
struct inode {int dummy; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmdrop (scalar_t__) ; 
 int seq_release_private (struct inode*,struct file*) ; 

__attribute__((used)) static int proc_map_release(struct inode *inode, struct file *file)
{
	struct seq_file *seq = file->private_data;
	struct proc_maps_private *priv = seq->private;

	if (priv->mm)
		mmdrop(priv->mm);

	return seq_release_private(inode, file);
}