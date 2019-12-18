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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 scalar_t__ ENOPROTOOPT ; 
 int /*<<< orphan*/  NN_PUB ; 
 int /*<<< orphan*/  NN_SUB ; 
 int /*<<< orphan*/  NN_SUB_SUBSCRIBE ; 
 int /*<<< orphan*/  SOCKET_ADDRESS ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 scalar_t__ nn_errno () ; 
 int nn_getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t*) ; 
 int nn_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
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
    int pub1;
    int pub2;
    int sub1;
    int sub2;
    char buf [8];
    size_t sz;

    pub1 = test_socket (AF_SP, NN_PUB);
    test_bind (pub1, SOCKET_ADDRESS);
    sub1 = test_socket (AF_SP, NN_SUB);
    rc = nn_setsockopt (sub1, NN_SUB, NN_SUB_SUBSCRIBE, "", 0);
    errno_assert (rc == 0);
    sz = sizeof (buf);
    rc = nn_getsockopt (sub1, NN_SUB, NN_SUB_SUBSCRIBE, buf, &sz);
    nn_assert (rc == -1 && nn_errno () == ENOPROTOOPT);
    test_connect (sub1, SOCKET_ADDRESS);
    sub2 = test_socket (AF_SP, NN_SUB);
    rc = nn_setsockopt (sub2, NN_SUB, NN_SUB_SUBSCRIBE, "", 0);
    errno_assert (rc == 0);
    test_connect (sub2, SOCKET_ADDRESS);

    /*  Wait till connections are established to prevent message loss. */
    nn_sleep (10);

    test_send (pub1, "0123456789012345678901234567890123456789");
    test_recv (sub1, "0123456789012345678901234567890123456789");
    test_recv (sub2, "0123456789012345678901234567890123456789");

    test_close (pub1);
    test_close (sub1);
    test_close (sub2);

    /*  Check receiving messages from two publishers. */

    sub1 = test_socket (AF_SP, NN_SUB);
    rc = nn_setsockopt (sub1, NN_SUB, NN_SUB_SUBSCRIBE, "", 0);
    errno_assert (rc == 0);
    test_bind (sub1, SOCKET_ADDRESS);
    pub1 = test_socket (AF_SP, NN_PUB);
    test_connect (pub1, SOCKET_ADDRESS);
    pub2 = test_socket (AF_SP, NN_PUB);
    test_connect (pub2, SOCKET_ADDRESS);
    nn_sleep (100);

    test_send (pub1, "0123456789012345678901234567890123456789");
    test_send (pub2, "0123456789012345678901234567890123456789");
    test_recv (sub1, "0123456789012345678901234567890123456789");
    test_recv (sub1, "0123456789012345678901234567890123456789");

    test_close (pub2);
    test_close (pub1);
    test_close (sub1);

    return 0;
}