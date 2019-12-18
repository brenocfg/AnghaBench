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
 scalar_t__ strcmp (char*,char const*) ; 

int masscan_conf_contains(const char *x, int argc, char **argv)
{
    int i;

    for (i=0; i<argc; i++) {
        if (strcmp(argv[i], x) == 0)
            return 1;
    }

    return 0;
}