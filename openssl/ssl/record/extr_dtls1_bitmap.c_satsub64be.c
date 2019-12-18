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
typedef  scalar_t__ uint64_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  n2l8 (unsigned char const*,scalar_t__) ; 

__attribute__((used)) static int satsub64be(const unsigned char *v1, const unsigned char *v2)
{
    int64_t ret;
    uint64_t l1, l2;

    n2l8(v1, l1);
    n2l8(v2, l2);

    ret = l1 - l2;

    /* We do not permit wrap-around */
    if (l1 > l2 && ret < 0)
        return 128;
    else if (l2 > l1 && ret > 0)
        return -128;

    if (ret > 128)
        return 128;
    else if (ret < -128)
        return -128;
    else
        return (int)ret;
}