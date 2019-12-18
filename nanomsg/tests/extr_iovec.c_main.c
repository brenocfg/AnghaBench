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
struct nn_msghdr {int msg_iovlen; struct nn_iovec* msg_iov; } ;
struct nn_iovec {char* iov_base; int iov_len; } ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 int /*<<< orphan*/  NN_PAIR ; 
 int /*<<< orphan*/  SOCKET_ADDRESS ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (struct nn_msghdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int nn_recvmsg (int,struct nn_msghdr*,int /*<<< orphan*/ ) ; 
 int nn_sendmsg (int,struct nn_msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bind (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,int /*<<< orphan*/ ) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main ()
{
    int rc;
    int sb;
    int sc;
    struct nn_iovec iov [2];
    struct nn_msghdr hdr;
    char buf [6];

    sb = test_socket (AF_SP, NN_PAIR);
    test_bind (sb, SOCKET_ADDRESS);
    sc = test_socket (AF_SP, NN_PAIR);
    test_connect (sc, SOCKET_ADDRESS);

    iov [0].iov_base = "AB";
    iov [0].iov_len = 2;
    iov [1].iov_base = "CDEF";
    iov [1].iov_len = 4;
    memset (&hdr, 0, sizeof (hdr));
    hdr.msg_iov = iov;
    hdr.msg_iovlen = 2;
    rc = nn_sendmsg (sc, &hdr, 0);
    errno_assert (rc >= 0);
    nn_assert (rc == 6);

    iov [0].iov_base = buf;
    iov [0].iov_len = 4;
    iov [1].iov_base = buf + 4;
    iov [1].iov_len = 2;
    memset (&hdr, 0, sizeof (hdr));
    hdr.msg_iov = iov;
    hdr.msg_iovlen = 2;
    rc = nn_recvmsg (sb, &hdr, 0);
    errno_assert (rc >= 0);
    nn_assert (rc == 6);
    nn_assert (memcmp (buf, "ABCDEF", 6) == 0);

    test_close (sc);
    test_close (sb);

    return 0;
}