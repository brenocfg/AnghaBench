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

int opt_isdir(const char *name)
{
# if defined(S_ISDIR)
    struct stat st;

    if (stat(name, &st) == 0)
        return S_ISDIR(st.st_mode);
    else
        return -1;
# else
    return -1;
# endif
}