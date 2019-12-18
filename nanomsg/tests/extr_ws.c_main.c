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
 scalar_t__ EINVAL ; 
 scalar_t__ ENODEV ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  NN_PAIR ; 
 int /*<<< orphan*/  NN_RCVMAXSIZE ; 
 int /*<<< orphan*/  NN_RCVTIMEO ; 
 int /*<<< orphan*/  NN_SNDTIMEO ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  NN_WS ; 
 int /*<<< orphan*/  NN_WS_MSG_TYPE ; 
 int NN_WS_MSG_TYPE_BINARY ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int /*<<< orphan*/  get_test_port (int,char const**) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int nn_bind (int,char*) ; 
 int nn_connect (int,char*) ; 
 scalar_t__ nn_errno () ; 
 int nn_getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 int nn_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  nn_sleep (int) ; 
 char* socket_address ; 
 int /*<<< orphan*/  test_addr_from (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bind (int,char*) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,char*) ; 
 int /*<<< orphan*/  test_drop (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_recv (int,char*) ; 
 int /*<<< orphan*/  test_send (int,char*) ; 
 int /*<<< orphan*/  test_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_text () ; 

int main (int argc, const char *argv[])
{
    int rc;
    int sb;
    int sc;
    int sb2;
    int opt;
    size_t sz;
    int i;
    char any_address[128];

    test_addr_from (socket_address, "ws", "127.0.0.1",
            get_test_port (argc, argv));

    test_addr_from (any_address, "ws", "*",
            get_test_port (argc, argv));

    /*  Try closing bound but unconnected socket. */
    sb = test_socket (AF_SP, NN_PAIR);
    test_bind (sb, any_address);
    test_close (sb);

    /*  Try closing a TCP socket while it not connected. At the same time
        test specifying the local address for the connection. */
    sc = test_socket (AF_SP, NN_PAIR);
    test_connect (sc, socket_address);
    test_close (sc);

    /*  Open the socket anew. */
    sc = test_socket (AF_SP, NN_PAIR);

    /*  Check socket options. */
    sz = sizeof (opt);
    rc = nn_getsockopt (sc, NN_WS, NN_WS_MSG_TYPE, &opt, &sz);
    errno_assert (rc == 0);
    nn_assert (sz == sizeof (opt));
    nn_assert (opt == NN_WS_MSG_TYPE_BINARY);

    /*  Default port 80 should be assumed if not explicitly declared. */
    rc = nn_connect (sc, "ws://127.0.0.1");
    errno_assert (rc >= 0);

    /*  Try using invalid address strings. */
    rc = nn_connect (sc, "ws://*:");
    nn_assert (rc < 0);
    errno_assert (nn_errno () == EINVAL);
    rc = nn_connect (sc, "ws://*:1000000");
    nn_assert (rc < 0);
    errno_assert (nn_errno () == EINVAL);
    rc = nn_connect (sc, "ws://*:some_port");
    nn_assert (rc < 0);
    rc = nn_connect (sc, "ws://eth10000;127.0.0.1:5555");
    nn_assert (rc < 0);
    errno_assert (nn_errno () == ENODEV);

    rc = nn_bind (sc, "ws://127.0.0.1:");
    nn_assert (rc < 0);
    errno_assert (nn_errno () == EINVAL);
    rc = nn_bind (sc, "ws://127.0.0.1:1000000");
    nn_assert (rc < 0);
    errno_assert (nn_errno () == EINVAL);
    rc = nn_bind (sc, "ws://eth10000:5555");
    nn_assert (rc < 0);
    errno_assert (nn_errno () == ENODEV);

    rc = nn_connect (sc, "ws://:5555");
    nn_assert (rc < 0);
    errno_assert (nn_errno () == EINVAL);
    rc = nn_connect (sc, "ws://-hostname:5555");
    nn_assert (rc < 0);
    errno_assert (nn_errno () == EINVAL);
    rc = nn_connect (sc, "ws://abc.123.---.#:5555");
    nn_assert (rc < 0);
    errno_assert (nn_errno () == EINVAL);
    rc = nn_connect (sc, "ws://[::1]:5555");
    nn_assert (rc < 0);
    errno_assert (nn_errno () == EINVAL);
    rc = nn_connect (sc, "ws://abc...123:5555");
    nn_assert (rc < 0);
    errno_assert (nn_errno () == EINVAL);
    rc = nn_connect (sc, "ws://.123:5555");
    nn_assert (rc < 0);
    errno_assert (nn_errno () == EINVAL);

    test_close (sc);

    sb = test_socket (AF_SP, NN_PAIR);
    test_bind (sb, socket_address);
    sc = test_socket (AF_SP, NN_PAIR);
    test_connect (sc, socket_address);

    /*  Ping-pong test. */
    for (i = 0; i != 100; ++i) {

        test_send (sc, "ABC");
        test_recv (sb, "ABC");

        test_send (sb, "DEF");
        test_recv (sc, "DEF");
    }

    /*  Batch transfer test. */
    for (i = 0; i != 100; ++i) {
        test_send (sc, "0123456789012345678901234567890123456789");
    }
    for (i = 0; i != 100; ++i) {
        test_recv (sb, "0123456789012345678901234567890123456789");
    }

    test_close (sc);
    test_close (sb);

    /*  Test two sockets binding to the same address. */
    sb = test_socket (AF_SP, NN_PAIR);
    test_bind (sb, socket_address);
    sb2 = test_socket (AF_SP, NN_PAIR);

    rc = nn_bind (sb2, socket_address);
    nn_assert (rc < 0);
    errno_assert (nn_errno () == EADDRINUSE);
    test_close(sb);
    test_close(sb2);

    /*  Test that NN_RCVMAXSIZE can be -1, but not lower */
    sb = test_socket (AF_SP, NN_PAIR);
    opt = -1;
    rc = nn_setsockopt (sb, NN_SOL_SOCKET, NN_RCVMAXSIZE, &opt, sizeof (opt));
    nn_assert (rc >= 0);
    opt = -2;
    rc = nn_setsockopt (sb, NN_SOL_SOCKET, NN_RCVMAXSIZE, &opt, sizeof (opt));
    nn_assert (rc < 0);
    errno_assert (nn_errno () == EINVAL);
    test_close (sb);

    /*  Test NN_RCVMAXSIZE limit */
    sb = test_socket (AF_SP, NN_PAIR);
    test_bind (sb, socket_address);
    sc = test_socket (AF_SP, NN_PAIR);
    test_connect (sc, socket_address);
    opt = 1000;
    test_setsockopt (sc, NN_SOL_SOCKET, NN_SNDTIMEO, &opt, sizeof (opt));
    nn_assert (opt == 1000);
    opt = 1000;
    test_setsockopt (sb, NN_SOL_SOCKET, NN_RCVTIMEO, &opt, sizeof (opt));
    nn_assert (opt == 1000);
    opt = 4;
    test_setsockopt (sb, NN_SOL_SOCKET, NN_RCVMAXSIZE, &opt, sizeof (opt));
    test_send (sc, "ABC");
    test_recv (sb, "ABC");
    test_send (sc, "ABCD");
    test_recv (sb, "ABCD");
    test_send (sc, "ABCDE");
    test_drop (sb, ETIMEDOUT);

    /*  Increase the size limit, reconnect, then try sending again. The reason a
        reconnect is necessary is because after a protocol violation, the
        connecting socket will not continue automatic reconnection attempts. */
    opt = 5;
    test_setsockopt (sb, NN_SOL_SOCKET, NN_RCVMAXSIZE, &opt, sizeof (opt));
    test_connect (sc, socket_address);
    test_send (sc, "ABCDE");
    test_recv (sb, "ABCDE");
    test_close (sb);
    test_close (sc);

    test_text ();

    /*  Test closing a socket that is waiting to connect. */
    sc = test_socket (AF_SP, NN_PAIR);
    test_connect (sc, socket_address);
    nn_sleep (100);
    test_close (sc);

    return 0;
}