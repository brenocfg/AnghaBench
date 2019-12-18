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
struct nn_thread {int dummy; } ;
typedef  int /*<<< orphan*/  maxttl ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 int /*<<< orphan*/  AF_SP_RAW ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  NN_MAXTTL ; 
 int /*<<< orphan*/  NN_RCVTIMEO ; 
 int /*<<< orphan*/  NN_RESPONDENT ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  NN_SURVEYOR ; 
 void* dev0 ; 
 void* dev1 ; 
 int /*<<< orphan*/  device ; 
 int get_test_port (int,char const**) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 scalar_t__ nn_errno () ; 
 int nn_getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 int nn_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  nn_sleep (int) ; 
 int /*<<< orphan*/  nn_term () ; 
 int /*<<< orphan*/  nn_thread_init (struct nn_thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_thread_term (struct nn_thread*) ; 
 int /*<<< orphan*/  socket_address_a ; 
 int /*<<< orphan*/  socket_address_b ; 
 int /*<<< orphan*/  test_addr_from (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  test_bind (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_drop (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_recv (int,char*) ; 
 int /*<<< orphan*/  test_send (int,char*) ; 
 int /*<<< orphan*/  test_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 void* test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main (int argc, const char *argv[])
{
    int end0;
    int end1;
    struct nn_thread thread1;
    int timeo;
    int maxttl;
    size_t sz;
    int rc;

    int port = get_test_port(argc, argv);

    test_addr_from(socket_address_a, "tcp", "127.0.0.1", port);
    test_addr_from(socket_address_b, "tcp", "127.0.0.1", port + 1);

    /*  Intialise the device sockets. */
    dev0 = test_socket (AF_SP_RAW, NN_RESPONDENT);
    dev1 = test_socket (AF_SP_RAW, NN_SURVEYOR);

    test_bind (dev0, socket_address_a);
    test_bind (dev1, socket_address_b);

    /*  Start the device. */
    nn_thread_init (&thread1, device, NULL);

    end0 = test_socket (AF_SP, NN_SURVEYOR);
    end1 = test_socket (AF_SP, NN_RESPONDENT);

    /*  Test the bi-directional device TTL */ 
    test_connect (end0, socket_address_a);
    test_connect (end1, socket_address_b);

    /*  Wait for TCP to establish. */
    nn_sleep (100);

    /*  Set up max receive timeout. */
    timeo = 100;
    test_setsockopt (end0, NN_SOL_SOCKET, NN_RCVTIMEO, &timeo, sizeof (timeo));
    timeo = 100;
    test_setsockopt (end1, NN_SOL_SOCKET, NN_RCVTIMEO, &timeo, sizeof (timeo));

    /*  Test default TTL is 8. */
    sz = sizeof (maxttl);
    maxttl = -1;
    rc = nn_getsockopt(end1, NN_SOL_SOCKET, NN_MAXTTL, &maxttl, &sz);
    nn_assert (rc == 0);
    nn_assert (sz == sizeof (maxttl));
    nn_assert (maxttl == 8);

    /*  Test to make sure option TTL cannot be set below 1. */
    maxttl = -1;
    rc = nn_setsockopt(end1, NN_SOL_SOCKET, NN_MAXTTL, &maxttl, sizeof (maxttl));
    nn_assert (rc < 0 && nn_errno () == EINVAL);
    nn_assert (maxttl == -1);
    maxttl = 0;
    rc = nn_setsockopt(end1, NN_SOL_SOCKET, NN_MAXTTL, &maxttl, sizeof (maxttl));
    nn_assert (rc < 0 && nn_errno () == EINVAL);
    nn_assert (maxttl == 0);

    /*  Test to set non-integer size */
    maxttl = 8;
    rc = nn_setsockopt(end1, NN_SOL_SOCKET, NN_MAXTTL, &maxttl, 1);
    nn_assert (rc < 0 && nn_errno () == EINVAL);
    nn_assert (maxttl == 8);

    /*  Pass a message between endpoints. */
    test_send (end0, "SURVEY");
    test_recv (end1, "SURVEY");

    /*  Now send a reply. */
    test_send (end1, "REPLYXYZ");
    test_recv (end0, "REPLYXYZ");

    /*  Now set the max TTL. */
    maxttl = 1;
    test_setsockopt (end0, NN_SOL_SOCKET, NN_MAXTTL, &maxttl, sizeof (maxttl));
    test_setsockopt (end1, NN_SOL_SOCKET, NN_MAXTTL, &maxttl, sizeof (maxttl));

    test_send (end0, "DROPTHIS");
    test_drop (end1, ETIMEDOUT);

    maxttl = 2;
    test_setsockopt (end0, NN_SOL_SOCKET, NN_MAXTTL, &maxttl, sizeof (maxttl));
    test_setsockopt (end1, NN_SOL_SOCKET, NN_MAXTTL, &maxttl, sizeof (maxttl));
    test_send (end0, "DONTDROP");
    test_recv (end1, "DONTDROP");

    /*  Clean up. */
    test_close (end0);
    test_close (end1);

    /*  Shut down the devices. */
    nn_term ();
    nn_thread_term (&thread1);

    return 0;
}