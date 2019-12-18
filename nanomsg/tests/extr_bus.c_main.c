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
 int /*<<< orphan*/  NN_BUS ; 
 int /*<<< orphan*/  SOCKET_ADDRESS_A ; 
 int /*<<< orphan*/  SOCKET_ADDRESS_B ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int nn_recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_sleep (int) ; 
 int /*<<< orphan*/  test_bind (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_send (int,char*) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main ()
{
    int rc;
    int bus1;
    int bus2;
    int bus3;
    char buf [3];

    /*  Create a simple bus topology consisting of 3 nodes. */
    bus1 = test_socket (AF_SP, NN_BUS);
    test_bind (bus1, SOCKET_ADDRESS_A);
    bus2 = test_socket (AF_SP, NN_BUS);
    test_bind (bus2, SOCKET_ADDRESS_B);
    test_connect (bus2, SOCKET_ADDRESS_A);
    bus3 = test_socket (AF_SP, NN_BUS);
    test_connect (bus3, SOCKET_ADDRESS_A);
    test_connect (bus3, SOCKET_ADDRESS_B);

    /*  Send a message from each node. */
    test_send (bus1, "A");
    test_send (bus2, "AB");
    test_send (bus3, "ABC");

    /*  Check that two messages arrived at each node. */
    rc = nn_recv (bus1, buf, 3, 0);
    errno_assert (rc >= 0);
    nn_assert (rc == 2 || rc == 3);
    rc = nn_recv (bus1, buf, 3, 0);
    errno_assert (rc >= 0);
    nn_assert (rc == 2 || rc == 3);
    rc = nn_recv (bus2, buf, 3, 0);
    errno_assert (rc >= 0);
    nn_assert (rc == 1 || rc == 3);
    rc = nn_recv (bus2, buf, 3, 0);
    errno_assert (rc >= 0);
    nn_assert (rc == 1 || rc == 3);
    rc = nn_recv (bus3, buf, 3, 0);
    errno_assert (rc >= 0);
    nn_assert (rc == 1 || rc == 2);
    rc = nn_recv (bus3, buf, 3, 0);
    errno_assert (rc >= 0);
    nn_assert (rc == 1 || rc == 2);

    /*  Wait till both connections are established. */
    nn_sleep (10);

    test_close (bus3);
    test_close (bus2);
    test_close (bus1);

    return 0;
}