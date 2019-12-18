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
typedef  int /*<<< orphan*/  sndprio ;
typedef  int /*<<< orphan*/  rcvprio ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  NN_DONTWAIT ; 
 int /*<<< orphan*/  NN_PULL ; 
 int /*<<< orphan*/  NN_PUSH ; 
 int /*<<< orphan*/  NN_RCVPRIO ; 
 int /*<<< orphan*/  NN_SNDPRIO ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  SOCKET_ADDRESS_A ; 
 int /*<<< orphan*/  SOCKET_ADDRESS_B ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 scalar_t__ nn_errno () ; 
 int nn_send (int,char*,int,int /*<<< orphan*/ ) ; 
 int nn_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  nn_sleep (int) ; 
 int /*<<< orphan*/  test_bind (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_recv (int,char*) ; 
 int /*<<< orphan*/  test_send (int,char*) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main ()
{
    int rc;
    int push1;
    int push2;
    int pull1;
    int pull2;
    int sndprio;
    int rcvprio;

    /*  Test send priorities. */

    pull1 = test_socket (AF_SP, NN_PULL);
    test_bind (pull1, SOCKET_ADDRESS_A);
    pull2 = test_socket (AF_SP, NN_PULL);
    test_bind (pull2, SOCKET_ADDRESS_B);
    push1 = test_socket (AF_SP, NN_PUSH);
    sndprio = 1;
    rc = nn_setsockopt (push1, NN_SOL_SOCKET, NN_SNDPRIO,
        &sndprio, sizeof (sndprio));
    errno_assert (rc == 0);
    test_connect (push1, SOCKET_ADDRESS_A);
    sndprio = 2;
    rc = nn_setsockopt (push1, NN_SOL_SOCKET, NN_SNDPRIO,
        &sndprio, sizeof (sndprio));
    errno_assert (rc == 0);
    test_connect (push1, SOCKET_ADDRESS_B);

    test_send (push1, "ABC");
    test_send (push1, "DEF");
    test_recv (pull1, "ABC");
    test_recv (pull1, "DEF");

    test_close (pull1);
    test_close (push1);
    test_close (pull2);

    /*  Test receive priorities. */

    push1 = test_socket (AF_SP, NN_PUSH);
    test_bind (push1, SOCKET_ADDRESS_A);
    push2 = test_socket (AF_SP, NN_PUSH);
    test_bind (push2, SOCKET_ADDRESS_B);
    pull1 = test_socket (AF_SP, NN_PULL);
    rcvprio = 2;
    rc = nn_setsockopt (pull1, NN_SOL_SOCKET, NN_RCVPRIO,
        &rcvprio, sizeof (rcvprio));
    errno_assert (rc == 0);
    test_connect (pull1, SOCKET_ADDRESS_A);
    rcvprio = 1;
    rc = nn_setsockopt (pull1, NN_SOL_SOCKET, NN_RCVPRIO,
        &rcvprio, sizeof (rcvprio));
    errno_assert (rc == 0);
    test_connect (pull1, SOCKET_ADDRESS_B);

    test_send (push1, "ABC");
    test_send (push2, "DEF");
    nn_sleep (100);
    test_recv (pull1, "DEF");
    test_recv (pull1, "ABC");

    test_close (pull1);
    test_close (push2);
    test_close (push1);

    /*  Test removing a pipe from the list. */

    push1 = test_socket (AF_SP, NN_PUSH);
    test_bind (push1, SOCKET_ADDRESS_A);
    pull1 = test_socket (AF_SP, NN_PULL);
    test_connect (pull1, SOCKET_ADDRESS_A);

    test_send (push1, "ABC");
    test_recv (pull1, "ABC");
    test_close (pull1);

    rc = nn_send (push1, "ABC", 3, NN_DONTWAIT);
    nn_assert (rc == -1 && nn_errno() == EAGAIN);

    pull1 = test_socket (AF_SP, NN_PULL);
    test_connect (pull1, SOCKET_ADDRESS_A);

    test_send (push1, "ABC");
    test_recv (pull1, "ABC");
    test_close (pull1);
    test_close (push1);

    return 0;
}