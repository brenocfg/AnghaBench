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

int
_npy_signbit_d(double x)
{
    union
    {
        double d;
        short s[4];
        int i[2];
    } u;

    u.d = x;

#if NPY_SIZEOF_INT == 4

#ifdef WORDS_BIGENDIAN /* defined in pyconfig.h */
    return u.i[0] < 0;
#else
    return u.i[1] < 0;
#endif

#else  /* NPY_SIZEOF_INT != 4 */

#ifdef WORDS_BIGENDIAN
    return u.s[0] < 0;
#else
    return u.s[3] < 0;
#endif

#endif  /* NPY_SIZEOF_INT */
}