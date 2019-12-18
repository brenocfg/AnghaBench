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
struct platform_state_group {scalar_t__ groupname; TYPE_1__* gr; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_2__ {int /*<<< orphan*/  gr_gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ setgid (int /*<<< orphan*/ ) ; 
 scalar_t__ setgroups (int,int /*<<< orphan*/ *) ; 

void
platform_group_set(const struct platform_state_group *state)
{
#if defined(HAVE_GETGRNAM) && defined(HAVE_SETGID)
    if (state->groupname && state->gr)
    {
        if (setgid(state->gr->gr_gid))
        {
            msg(M_ERR, "setgid('%s') failed", state->groupname);
        }
        msg(M_INFO, "GID set to %s", state->groupname);
#ifdef HAVE_SETGROUPS
        {
            gid_t gr_list[1];
            gr_list[0] = state->gr->gr_gid;
            if (setgroups(1, gr_list))
            {
                msg(M_ERR, "setgroups('%s') failed", state->groupname);
            }
        }
#endif
    }
#endif
}