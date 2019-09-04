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
struct dentry {struct dentry* d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  cifs_set_time (struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void
renew_parental_timestamps(struct dentry *direntry)
{
	/* BB check if there is a way to get the kernel to do this or if we
	   really need this */
	do {
		cifs_set_time(direntry, jiffies);
		direntry = direntry->d_parent;
	} while (!IS_ROOT(direntry));
}