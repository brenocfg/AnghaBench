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
 int ENXIO ; 
 int EOPNOTSUPP ; 
 unsigned int console (struct inode*) ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int use_attributes (struct inode*) ; 
 int use_unicode (struct inode*) ; 
 int /*<<< orphan*/  vc_cons_allocated (unsigned int) ; 

__attribute__((used)) static int
vcs_open(struct inode *inode, struct file *filp)
{
	unsigned int currcons = console(inode);
	bool attr = use_attributes(inode);
	bool uni_mode = use_unicode(inode);
	int ret = 0;

	/* we currently don't support attributes in unicode mode */
	if (attr && uni_mode)
		return -EOPNOTSUPP;

	console_lock();
	if(currcons && !vc_cons_allocated(currcons-1))
		ret = -ENXIO;
	console_unlock();
	return ret;
}