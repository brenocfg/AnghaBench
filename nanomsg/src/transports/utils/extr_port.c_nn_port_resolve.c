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

int nn_port_resolve (const char *port, size_t portlen)
{
    int res;
    size_t i;

    res = 0;
    for (i = 0; i != portlen; ++i) {
        if (port [i] < '0' || port [i] > '9')
            return -EINVAL;
        res *= 10;
        res += port [i] - '0';
        if (res > 0xffff)
            return -EINVAL;
    }

    /*  Port 0 has special meaning (assign an ephemeral port to the socket),
        thus it is illegal to use it in the connection string. */
    if (res == 0)
        return -EINVAL;

    return res;
}