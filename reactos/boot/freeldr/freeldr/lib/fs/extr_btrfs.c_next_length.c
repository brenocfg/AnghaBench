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
 int BTRFS_NAME_MAX ; 

__attribute__((used)) static inline int next_length(const char *path)
{
    int res = 0;
    while (*path != '\0' && *path != '/' && *path != '\\' && res <= BTRFS_NAME_MAX)
        ++res, ++path;
    return res;
}