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
 int /*<<< orphan*/  mp_path_separators ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 
 size_t strlen (char*) ; 

void mp_path_strip_trailing_separator(char *path)
{
    size_t len = strlen(path);
    if (len > 0 && strchr(mp_path_separators, path[len - 1]))
        path[len - 1] = '\0';
}