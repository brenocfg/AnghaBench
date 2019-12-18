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
struct platform_state_user {TYPE_1__* pw; } ;
struct TYPE_2__ {int pw_uid; } ;

/* Variables and functions */

__attribute__((used)) static inline int
platform_state_user_uid(const struct platform_state_user *s)
{
#if defined(HAVE_GETPWNAM) && defined(HAVE_SETUID)
    if (s->pw)
    {
        return s->pw->pw_uid;
    }
#endif
    return -1;
}