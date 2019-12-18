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
struct file {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  aa_sfs_profiles_op ; 
 int /*<<< orphan*/  policy_view_capable (int /*<<< orphan*/ *) ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int profiles_open(struct inode *inode, struct file *file)
{
	if (!policy_view_capable(NULL))
		return -EACCES;

	return seq_open(file, &aa_sfs_profiles_op);
}