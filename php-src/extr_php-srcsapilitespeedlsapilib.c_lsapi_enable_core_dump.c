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

/* Variables and functions */
 int /*<<< orphan*/  PR_SET_DUMPABLE ; 
 int /*<<< orphan*/  perror (char*) ; 
 int prctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_enable_core_dump ; 

__attribute__((used)) static void lsapi_enable_core_dump(void)
{
#if defined(__FreeBSD__ ) || defined(__NetBSD__) || defined(__OpenBSD__) \
    || defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
    int  mib[2];
    size_t len;

    len = 2;
    if ( sysctlnametomib("kern.sugid_coredump", mib, &len) == 0 )
    {
        len = sizeof(s_enable_core_dump);
        if (sysctl(mib, 2, NULL, 0, &s_enable_core_dump, len) == -1)
            perror( "sysctl: Failed to set 'kern.sugid_coredump', "
                    "core dump may not be available!");
    }


#endif

#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
    if (prctl(PR_SET_DUMPABLE, s_enable_core_dump,0,0,0) == -1)
        perror( "prctl: Failed to set dumpable, "
                    "core dump may not be available!");
#endif
}