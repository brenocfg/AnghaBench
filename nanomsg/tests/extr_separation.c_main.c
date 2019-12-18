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
typedef  int /*<<< orphan*/  timeo ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  NN_PAIR ; 
 int /*<<< orphan*/  NN_PULL ; 
 int /*<<< orphan*/  NN_SNDTIMEO ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 char* SOCKET_ADDRESS_INPROC ; 
 char* SOCKET_ADDRESS_IPC ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int /*<<< orphan*/  get_test_port (int,char const**) ; 
 scalar_t__ nn_errno () ; 
 int nn_send (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_addr_from (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bind (int,char*) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,char*) ; 
 int /*<<< orphan*/  test_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main (int argc, const char *argv[])
{
    int rc;
    int pair;
    int pull;
    int timeo;
    char socket_address_tcp[128];

    test_addr_from(socket_address_tcp, "tcp", "127.0.0.1",
            get_test_port(argc, argv));

    /*  Inproc: Bind first, connect second. */
    pair = test_socket (AF_SP, NN_PAIR);
    test_bind (pair, SOCKET_ADDRESS_INPROC);
    pull = test_socket (AF_SP, NN_PULL);
    test_connect (pull, SOCKET_ADDRESS_INPROC);
    timeo = 100;
    test_setsockopt (pair, NN_SOL_SOCKET, NN_SNDTIMEO,
        &timeo, sizeof (timeo));
    rc = nn_send (pair, "ABC", 3, 0);
    errno_assert (rc < 0 && nn_errno () == ETIMEDOUT);
    test_close (pull);
    test_close (pair);

    /*  Inproc: Connect first, bind second. */
    pull = test_socket (AF_SP, NN_PULL);
    test_connect (pull, SOCKET_ADDRESS_INPROC);
    pair = test_socket (AF_SP, NN_PAIR);
    test_bind (pair, SOCKET_ADDRESS_INPROC);
    timeo = 100;
    test_setsockopt (pair, NN_SOL_SOCKET, NN_SNDTIMEO,
        &timeo, sizeof (timeo));
    rc = nn_send (pair, "ABC", 3, 0);
    errno_assert (rc < 0 && nn_errno () == ETIMEDOUT);
    test_close (pull);
    test_close (pair);

#if !defined NN_HAVE_WINDOWS && !defined NN_HAVE_WSL

    /*  IPC */
    pair = test_socket (AF_SP, NN_PAIR);
    test_bind (pair, SOCKET_ADDRESS_IPC);
    pull = test_socket (AF_SP, NN_PULL);
    test_connect (pull, SOCKET_ADDRESS_IPC);
    timeo = 100;
    test_setsockopt (pair, NN_SOL_SOCKET, NN_SNDTIMEO,
        &timeo, sizeof (timeo));
    rc = nn_send (pair, "ABC", 3, 0);
    errno_assert (rc < 0 && nn_errno () == ETIMEDOUT);
    test_close (pull);
    test_close (pair);

#endif

    /*  TCP */
    pair = test_socket (AF_SP, NN_PAIR);
    test_bind (pair, socket_address_tcp);
    pull = test_socket (AF_SP, NN_PULL);
    test_connect (pull, socket_address_tcp);
    timeo = 100;
    test_setsockopt (pair, NN_SOL_SOCKET, NN_SNDTIMEO,
        &timeo, sizeof (timeo));
    rc = nn_send (pair, "ABC", 3, 0);
    errno_assert (rc < 0 && nn_errno () == ETIMEDOUT);
    test_close (pull);
    test_close (pair);

    return 0;
}