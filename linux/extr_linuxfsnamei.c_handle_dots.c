#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mnt; } ;
struct nameidata {int flags; TYPE_1__ root; } ;

/* Variables and functions */
 int LAST_DOTDOT ; 
 int LOOKUP_RCU ; 
 int follow_dotdot (struct nameidata*) ; 
 int follow_dotdot_rcu (struct nameidata*) ; 
 int /*<<< orphan*/  set_root (struct nameidata*) ; 

__attribute__((used)) static inline int handle_dots(struct nameidata *nd, int type)
{
	if (type == LAST_DOTDOT) {
		if (!nd->root.mnt)
			set_root(nd);
		if (nd->flags & LOOKUP_RCU) {
			return follow_dotdot_rcu(nd);
		} else
			return follow_dotdot(nd);
	}
	return 0;
}