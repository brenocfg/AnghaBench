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
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 long sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long _find_pagesize(void) {
#if defined(HAVE_SYSCONF) && defined(_SC_PAGESIZE)
    return sysconf(_SC_PAGESIZE);
#else
    // A good guess.
    return 4096;
#endif
}