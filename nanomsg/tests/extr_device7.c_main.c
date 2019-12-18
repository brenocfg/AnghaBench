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
struct nn_thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 int /*<<< orphan*/  NN_REP ; 
 int /*<<< orphan*/  NN_REQ ; 
 int /*<<< orphan*/  device5 ; 
 int /*<<< orphan*/  device6 ; 
 int get_test_port (int,char const**) ; 
 int /*<<< orphan*/  nn_sleep (int) ; 
 int /*<<< orphan*/  nn_term () ; 
 int /*<<< orphan*/  nn_thread_init (struct nn_thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_thread_term (struct nn_thread*) ; 
 int /*<<< orphan*/  socket_address_h ; 
 int /*<<< orphan*/  socket_address_j ; 
 int /*<<< orphan*/  test_addr_from (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_recv (int,char*) ; 
 int /*<<< orphan*/  test_send (int,char*) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main (int argc, const char *argv[])
{
    int end0;
    int end1;
    struct nn_thread thread5;
    struct nn_thread thread6;

    int port = get_test_port(argc, argv);

    test_addr_from(socket_address_h, "tcp", "127.0.0.1", port);
    test_addr_from(socket_address_j, "tcp", "127.0.0.1", port + 1);

    /*  Test the bi-directional device with REQ/REP (headers). */

    /*  Start the devices. */
    nn_thread_init (&thread5, device5, NULL);
    nn_thread_init (&thread6, device6, NULL);

    /*  Create two sockets to connect to the device. */
    end0 = test_socket (AF_SP, NN_REQ);
    test_connect (end0, socket_address_h);
    end1 = test_socket (AF_SP, NN_REP);
    test_connect (end1, socket_address_j);

    /*  Wait for TCP to establish. */
    nn_sleep (1000);

    /*  Pass a message between endpoints. */
    test_send (end0, "XYZ");
    test_recv (end1, "XYZ");

    /*  Now send a reply. */
    test_send (end1, "REPLYXYZ");
    test_recv (end0, "REPLYXYZ");

    /*  Clean up. */
    test_close (end0);
    test_close (end1);

    /*  Shut down the devices. */
    nn_term ();
    nn_thread_term (&thread5);
    nn_thread_term (&thread6);

    return 0;
}