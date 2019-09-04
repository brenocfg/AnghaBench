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
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */

int
mch_copy_file_attribute(char_u *from, char_u *to)
{
#ifdef FEAT_MBYTE
    /* File streams only work on Windows NT and later. */
    PlatformId();
    if (g_PlatformId == VER_PLATFORM_WIN32_NT)
	copy_infostreams(from, to);
#endif
    return 0;
}