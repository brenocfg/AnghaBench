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
typedef  int /*<<< orphan*/  resend_ivl ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 scalar_t__ EFSM ; 
 int /*<<< orphan*/  NN_RCVTIMEO ; 
 int /*<<< orphan*/  NN_REP ; 
 int /*<<< orphan*/  NN_REQ ; 
 int /*<<< orphan*/  NN_REQ_RESEND_IVL ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  SOCKET_ADDRESS ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 scalar_t__ nn_errno () ; 
 int nn_recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int nn_send (int,char*,int,int /*<<< orphan*/ ) ; 
 int nn_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  test_bind (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_recv (int,char*) ; 
 int /*<<< orphan*/  test_send (int,char*) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main ()
{
    int rc;
    int rep1;
    int rep2;
    int req1;
    int req2;
    int resend_ivl;
    char buf [7];
    int timeo;

    /*  Test req/rep with full socket types. */
    rep1 = test_socket (AF_SP, NN_REP);
    test_bind (rep1, SOCKET_ADDRESS);
    req1 = test_socket (AF_SP, NN_REQ);
    test_connect (req1, SOCKET_ADDRESS);
    req2 = test_socket (AF_SP, NN_REQ);
    test_connect (req2, SOCKET_ADDRESS);

    /*  Check invalid sequence of sends and recvs. */
    rc = nn_send (rep1, "ABC", 3, 0);
    nn_assert (rc == -1 && nn_errno () == EFSM);
    rc = nn_recv (req1, buf, sizeof (buf), 0);
    nn_assert (rc == -1 && nn_errno () == EFSM);

    /*  Check fair queueing the requests. */
    test_send (req2, "ABC");
    test_recv (rep1, "ABC");
    test_send (rep1, "ABC");
    test_recv (req2, "ABC");

    test_send (req1, "ABC");
    test_recv (rep1, "ABC");
    test_send (rep1, "ABC");
    test_recv (req1, "ABC");

    test_close (rep1);
    test_close (req1);
    test_close (req2);

    /*  Check load-balancing of requests. */
    req1 = test_socket (AF_SP, NN_REQ);
    test_bind (req1, SOCKET_ADDRESS);
    rep1 = test_socket (AF_SP, NN_REP);
    test_connect (rep1, SOCKET_ADDRESS);
    rep2 = test_socket (AF_SP, NN_REP);
    test_connect (rep2, SOCKET_ADDRESS);

    test_send (req1, "ABC");
    test_recv (rep1, "ABC");
    test_send (rep1, "ABC");
    test_recv (req1, "ABC");

    test_send (req1, "ABC");
    test_recv (rep2, "ABC");
    test_send (rep2, "ABC");
    test_recv (req1, "ABC");

    test_close (rep2);
    test_close (rep1);
    test_close (req1);

    /*  Test re-sending of the request. */
    rep1 = test_socket (AF_SP, NN_REP);
    test_bind (rep1, SOCKET_ADDRESS);
    req1 = test_socket (AF_SP, NN_REQ);
    test_connect (req1, SOCKET_ADDRESS);
    resend_ivl = 100;
    rc = nn_setsockopt (req1, NN_REQ, NN_REQ_RESEND_IVL,
        &resend_ivl, sizeof (resend_ivl));
    errno_assert (rc == 0);

    test_send (req1, "ABC");
    test_recv (rep1, "ABC");
    /*  The following waits for request to be resent  */
    test_recv (rep1, "ABC");

    test_close (req1);
    test_close (rep1);

    /*  Check sending a request when the peer is not available. (It should
        be sent immediatelly when the peer comes online rather than relying
        on the resend algorithm. */
    req1 = test_socket (AF_SP, NN_REQ);
    test_connect (req1, SOCKET_ADDRESS);
    test_send (req1, "ABC");

    rep1 = test_socket (AF_SP, NN_REP);
    test_bind (rep1, SOCKET_ADDRESS);
    timeo = 200;
    rc = nn_setsockopt (rep1, NN_SOL_SOCKET, NN_RCVTIMEO,
       &timeo, sizeof (timeo));
    errno_assert (rc == 0);
    test_recv (rep1, "ABC");

    test_close (req1);
    test_close (rep1);

    /*  Check removing socket request sent to (It should
        be sent immediatelly to other peer rather than relying
        on the resend algorithm). */
    req1 = test_socket (AF_SP, NN_REQ);
    test_bind (req1, SOCKET_ADDRESS);
    rep1 = test_socket (AF_SP, NN_REP);
    test_connect (rep1, SOCKET_ADDRESS);
    rep2 = test_socket (AF_SP, NN_REP);
    test_connect (rep2, SOCKET_ADDRESS);

    timeo = 200;
    rc = nn_setsockopt (rep1, NN_SOL_SOCKET, NN_RCVTIMEO,
       &timeo, sizeof (timeo));
    errno_assert (rc == 0);
    rc = nn_setsockopt (rep2, NN_SOL_SOCKET, NN_RCVTIMEO,
       &timeo, sizeof (timeo));
    errno_assert (rc == 0);

    test_send (req1, "ABC");
    /*  We got request through rep1  */
    test_recv (rep1, "ABC");
    /*  But instead replying we simulate crash  */
    test_close (rep1);
    /*  The rep2 should get request immediately  */
    test_recv (rep2, "ABC");
    /*  Let's check it's delivered well  */
    test_send (rep2, "REPLY");
    test_recv (req1, "REPLY");


    test_close (req1);
    test_close (rep2);

    /*  Test cancelling delayed request  */

    req1 = test_socket (AF_SP, NN_REQ);
    test_connect (req1, SOCKET_ADDRESS);
    test_send (req1, "ABC");
    test_send (req1, "DEF");

    rep1 = test_socket (AF_SP, NN_REP);
    test_bind (rep1, SOCKET_ADDRESS);
    timeo = 100;
    test_recv (rep1, "DEF");

    test_close (req1);
    test_close (rep1);

    return 0;
}