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
 int /*<<< orphan*/  NN_PULL ; 
 int /*<<< orphan*/  NN_PUSH ; 
 int /*<<< orphan*/  SOCKET_ADDRESS ; 
 int /*<<< orphan*/  nn_sleep (int) ; 
 int /*<<< orphan*/  test_bind (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_recv (int,char*) ; 
 int /*<<< orphan*/  test_send (int,char*) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main ()
{
    int push1;
    int push2;
    int pull1;
    int pull2;

    /*  Test fan-out. */

    push1 = test_socket (AF_SP, NN_PUSH);
    test_bind (push1, SOCKET_ADDRESS);
    pull1 = test_socket (AF_SP, NN_PULL);
    test_connect (pull1, SOCKET_ADDRESS);
    pull2 = test_socket (AF_SP, NN_PULL);
    test_connect (pull2, SOCKET_ADDRESS);

    /*  Wait till both connections are established to get messages spread
        evenly between the two pull sockets. */
    nn_sleep (10);

    test_send (push1, "ABC");
    test_send (push1, "DEF");

    test_recv (pull1, "ABC");
    test_recv (pull2, "DEF");

    test_close (push1);
    test_close (pull1);
    test_close (pull2);

    /*  Test fan-in. */

    pull1 = test_socket (AF_SP, NN_PULL);
    test_bind (pull1, SOCKET_ADDRESS);
    push1 = test_socket (AF_SP, NN_PUSH);
    test_connect (push1, SOCKET_ADDRESS);
    push2 = test_socket (AF_SP, NN_PUSH);
    test_connect (push2, SOCKET_ADDRESS);

    test_send (push1, "ABC");
    test_send (push2, "DEF");

    test_recv (pull1, "ABC");
    test_recv (pull1, "DEF");

    test_close (pull1);
    test_close (push1);
    test_close (push2);

    return 0;
}