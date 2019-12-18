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
struct dentry {int dummy; } ;
struct autofs_info {scalar_t__ last_used; } ;

/* Variables and functions */
 unsigned int AUTOFS_EXP_IMMEDIATE ; 
 struct autofs_info* autofs_dentry_ino (struct dentry*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_after (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int autofs_can_expire(struct dentry *dentry,
				    unsigned long timeout, unsigned int how)
{
	struct autofs_info *ino = autofs_dentry_ino(dentry);

	/* dentry in the process of being deleted */
	if (ino == NULL)
		return 0;

	if (!(how & AUTOFS_EXP_IMMEDIATE)) {
		/* Too young to die */
		if (!timeout || time_after(ino->last_used + timeout, jiffies))
			return 0;
	}
	return 1;
}