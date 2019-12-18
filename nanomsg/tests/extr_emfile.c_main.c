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
 int /*<<< orphan*/  AF_SP ; 
 scalar_t__ EMFILE ; 
 int MAX_SOCKETS ; 
 int /*<<< orphan*/  NN_PAIR ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int nn_close (int) ; 
 scalar_t__ nn_errno () ; 
 int nn_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main ()
{
    int rc;
    int i;
    int socks [MAX_SOCKETS];

    /*  First, just create as much SP sockets as possible. */
    for (i = 0; i != MAX_SOCKETS; ++i) {
        socks [i] = nn_socket (AF_SP, NN_PAIR);
        if (socks [i] < 0) {
            errno_assert (nn_errno () == EMFILE);
            break;
        }
    }
    while (1) {
        --i;
        if (i == -1)
            break;
        rc = nn_close (socks [i]);
        errno_assert (rc == 0);
    }

    return 0;
}