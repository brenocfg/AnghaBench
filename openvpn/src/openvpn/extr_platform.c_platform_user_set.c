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
struct platform_state_user {scalar_t__ username; TYPE_1__* pw; } ;
struct TYPE_2__ {int /*<<< orphan*/  pw_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ setuid (int /*<<< orphan*/ ) ; 

void
platform_user_set(const struct platform_state_user *state)
{
#if defined(HAVE_GETPWNAM) && defined(HAVE_SETUID)
    if (state->username && state->pw)
    {
        if (setuid(state->pw->pw_uid))
        {
            msg(M_ERR, "setuid('%s') failed", state->username);
        }
        msg(M_INFO, "UID set to %s", state->username);
    }
#endif
}