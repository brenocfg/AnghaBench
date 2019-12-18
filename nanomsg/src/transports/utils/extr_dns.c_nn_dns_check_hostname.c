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
 int EINVAL ; 

int nn_dns_check_hostname (const char *name, size_t namelen)
{
    int labelsz;

    /*  There has to be at least one label in the hostname.
        Additionally, hostnames are up to 255 characters long. */
    if (namelen < 1 || namelen > 255)
        return -EINVAL;

    /*  Hyphen can't be used as a first character of the hostname. */
    if (*name == '-')
        return -EINVAL;

    labelsz = 0;
    while (1) {

        /*  End of the hostname. */
        if (namelen == 0) {
            /*  Success! */
            return 0;
        }

        /*  End of a label. */
        if (*name == '.') {

            /*  The old label cannot be empty. */
            if (labelsz == 0)
                return -EINVAL;

            /*  Start new label. */
            labelsz = 0;
            ++name;
            --namelen;
            continue;
        }

        /*  Valid character. */
        if ((*name >= 'a' && *name <= 'z') ||
              (*name >= 'A' && *name <= 'Z') ||
              (*name >= '0' && *name <= '9') ||
              *name == '-') {
            ++name;
            --namelen;
            ++labelsz;

            /*  Labels longer than 63 charcters are not permitted. */
            if (labelsz > 63)
                return -EINVAL;

            continue;
        }

        /*  Invalid character. */
        return -EINVAL;
    }
}