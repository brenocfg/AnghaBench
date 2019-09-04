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
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 

errno_t strcpy_s(char *dst, size_t sizeof_dst, const char *src)
{
    size_t i;

    if (sizeof_dst == 0)
        return ERANGE;

    if (dst == NULL)
        return EINVAL;

    if (src == NULL) {
        dst[0] = 0;
        return EINVAL;
    }

    for (i=0; src[i]; i++) {
        if (i >= sizeof_dst) {
            dst[0] = 0;
            return ERANGE;
        } else
            dst[i] = src[i];
    }
    if (i >= sizeof_dst) {
        dst[0] = 0;
        return ERANGE;
    } else
        dst[i] = src[i];

    return 0;
}