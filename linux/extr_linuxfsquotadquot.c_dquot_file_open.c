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
struct file {int f_mode; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int dquot_initialize (struct inode*) ; 
 int generic_file_open (struct inode*,struct file*) ; 

int dquot_file_open(struct inode *inode, struct file *file)
{
	int error;

	error = generic_file_open(inode, file);
	if (!error && (file->f_mode & FMODE_WRITE))
		error = dquot_initialize(inode);
	return error;
}