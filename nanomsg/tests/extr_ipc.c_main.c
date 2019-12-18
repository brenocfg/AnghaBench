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
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 scalar_t__ EADDRINUSE ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  NN_DONTWAIT ; 
 int /*<<< orphan*/  NN_MSG ; 
 int /*<<< orphan*/  NN_PAIR ; 
 int /*<<< orphan*/  NN_RCVMAXSIZE ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  SOCKET_ADDRESS ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int nn_bind (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nn_errno () ; 
 int nn_recv (int,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nn_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t) ; 
 int /*<<< orphan*/  nn_sleep (int) ; 
 int /*<<< orphan*/  test_bind (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_recv (int,char*) ; 
 int /*<<< orphan*/  test_send (int,char*) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main ()
{
#ifndef NN_HAVE_WSL
    int sb;
    int sc;
    int i;
    int s1, s2;
    void * dummy_buf;
    int rc;
    int opt;
    size_t opt_sz = sizeof (opt);

    int size;
    char * buf;

    /*  Try closing a IPC socket while it not connected. */
    sc = test_socket (AF_SP, NN_PAIR);
    test_connect (sc, SOCKET_ADDRESS);
    test_close (sc);

    /*  Open the socket anew. */
    sc = test_socket (AF_SP, NN_PAIR);
    test_connect (sc, SOCKET_ADDRESS);

    /*  Leave enough time for at least one re-connect attempt. */
    nn_sleep (200);

    sb = test_socket (AF_SP, NN_PAIR);
    test_bind (sb, SOCKET_ADDRESS);

    /*  Ping-pong test. */
    for (i = 0; i != 1; ++i) {
        test_send (sc, "0123456789012345678901234567890123456789");
        test_recv (sb, "0123456789012345678901234567890123456789");
        test_send (sb, "0123456789012345678901234567890123456789");
        test_recv (sc, "0123456789012345678901234567890123456789");
    }

    /*  Batch transfer test. */
    for (i = 0; i != 100; ++i) {
        test_send (sc, "XYZ");
    }
    for (i = 0; i != 100; ++i) {
        test_recv (sb, "XYZ");
    }

    /*  Send something large enough to trigger overlapped I/O on Windows. */
    size = 10000;
    buf = malloc (size);
    for (i = 0; i < size; ++i) {
        buf[i] = 48 + i % 10;
    }
    buf[size-1] = '\0';
    test_send (sc, buf);
    test_recv (sb, buf);
    free (buf);

    test_close (sc);
    test_close (sb);

    /*  Test whether connection rejection is handled decently. */
    sb = test_socket (AF_SP, NN_PAIR);
    test_bind (sb, SOCKET_ADDRESS);
    s1 = test_socket (AF_SP, NN_PAIR);
    test_connect (s1, SOCKET_ADDRESS);
    s2 = test_socket (AF_SP, NN_PAIR);
    test_connect (s2, SOCKET_ADDRESS);
    nn_sleep (100);
    test_close (s2);
    test_close (s1);
    test_close (sb);

/*  On Windows, CreateNamedPipeA does not run exclusively.
    We should look at fixing this, but it will require
    changing the usock code for Windows.  In the meantime just
    disable this test on Windows. */
#if !defined(NN_HAVE_WINDOWS)
    /*  Test two sockets binding to the same address. */
    sb = test_socket (AF_SP, NN_PAIR);
    test_bind (sb, SOCKET_ADDRESS);
    s1 = test_socket (AF_SP, NN_PAIR);
    rc = nn_bind (s1, SOCKET_ADDRESS);
    nn_assert (rc < 0);
    errno_assert (nn_errno () == EADDRINUSE);
    sc = test_socket (AF_SP, NN_PAIR);
    test_connect (sc, SOCKET_ADDRESS);
    nn_sleep (100);
    test_send (sb, "ABC");
    test_recv (sc, "ABC");
    test_close (sb);
    test_close (sc);
    test_close (s1);
#endif

    /*  Test NN_RCVMAXSIZE limit */
    sb = test_socket (AF_SP, NN_PAIR);
    test_bind (sb, SOCKET_ADDRESS);
    s1 = test_socket (AF_SP, NN_PAIR);
    test_connect (s1, SOCKET_ADDRESS);
    opt = 4;
    rc = nn_setsockopt (sb, NN_SOL_SOCKET, NN_RCVMAXSIZE, &opt, opt_sz);
    nn_assert (rc == 0);
    nn_sleep (100);
    test_send (s1, "ABCD");
    test_recv (sb, "ABCD");
    test_send (s1, "ABCDE");
    /*  Without sleep nn_recv returns EAGAIN even for string
        of acceptable size, so false positives are possible. */
    nn_sleep (100);
    rc = nn_recv (sb, &dummy_buf, NN_MSG, NN_DONTWAIT);
    nn_assert (rc < 0);
    errno_assert (nn_errno () == EAGAIN);
    test_close (sb);
    test_close (s1);

    /*  Test that NN_RCVMAXSIZE can be -1, but not lower */
    sb = test_socket (AF_SP, NN_PAIR);
    opt = -1;
    rc = nn_setsockopt (sb, NN_SOL_SOCKET, NN_RCVMAXSIZE, &opt, opt_sz);
    nn_assert (rc >= 0);
    opt = -2;
    rc = nn_setsockopt (sb, NN_SOL_SOCKET, NN_RCVMAXSIZE, &opt, opt_sz);
    nn_assert (rc < 0);
    errno_assert (nn_errno () == EINVAL);
    test_close (sb);

    /*  Test closing a socket that is waiting to connect. */
    sc = test_socket (AF_SP, NN_PAIR);
    test_connect (sc, SOCKET_ADDRESS);
    nn_sleep (100);
    test_close (sc);
#endif /* NN_HAVE_WSL */

    return 0;
}