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
struct platform_state_group {TYPE_1__* gr; } ;
struct TYPE_2__ {int gr_gid; } ;

/* Variables and functions */

__attribute__((used)) static inline int
platform_state_group_gid(const struct platform_state_group *s)
{
#if defined(HAVE_GETGRNAM) && defined(HAVE_SETGID)
    if (s->gr)
    {
        return s->gr->gr_gid;
    }
#endif
    return -1;
}