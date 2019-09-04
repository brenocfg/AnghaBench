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
struct ci_hdrc {int role; TYPE_1__** roles; } ;
typedef  enum ci_role { ____Placeholder_ci_role } ci_role ;
struct TYPE_2__ {int (* start ) (struct ci_hdrc*) ;} ;

/* Variables and functions */
 int CI_ROLE_END ; 
 int EINVAL ; 
 int ENXIO ; 
 int stub1 (struct ci_hdrc*) ; 

__attribute__((used)) static inline int ci_role_start(struct ci_hdrc *ci, enum ci_role role)
{
	int ret;

	if (role >= CI_ROLE_END)
		return -EINVAL;

	if (!ci->roles[role])
		return -ENXIO;

	ret = ci->roles[role]->start(ci);
	if (!ret)
		ci->role = role;
	return ret;
}