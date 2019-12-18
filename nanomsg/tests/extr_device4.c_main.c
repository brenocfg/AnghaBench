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
 int /*<<< orphan*/  device4 ; 
 int get_test_port (int,char const**) ; 
 int /*<<< orphan*/  nn_sleep (int) ; 
 int /*<<< orphan*/  nn_term () ; 
 int /*<<< orphan*/  nn_thread_init (struct nn_thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_thread_term (struct nn_thread*) ; 
 int /*<<< orphan*/  socket_address_f ; 
 int /*<<< orphan*/  socket_address_g ; 
 int /*<<< orphan*/  test_addr_from (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_recv (int,char*) ; 
 int /*<<< orphan*/  test_send (int,char*) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main (int argc, const char *argv[])
{
    int endf;
    int endg;
    struct nn_thread thread4;

    int port = get_test_port(argc, argv);

    test_addr_from(socket_address_f, "tcp", "127.0.0.1", port);
    test_addr_from(socket_address_g, "tcp", "127.0.0.1", port + 1);

    /*  Test the bi-directional device with REQ/REP (headers). */

    /*  Start the device. */
    nn_thread_init (&thread4, device4, NULL);

    /*  Create two sockets to connect to the device. */
    endf = test_socket (AF_SP, NN_REQ);
    test_connect (endf, socket_address_f);
    endg = test_socket (AF_SP, NN_REP);
    test_connect (endg, socket_address_g);

    /*  Wait for TCP to establish. */
    nn_sleep (100);

    /*  Pass a message between endpoints. */
    test_send (endf, "XYZ");
    test_recv (endg, "XYZ");

    /*  Now send a reply. */
    test_send (endg, "REPLYXYZ");
    test_recv (endf, "REPLYXYZ");

    /*  Clean up. */
    test_close (endg);
    test_close (endf);

    /*  Shut down the devices. */
    nn_term ();
    nn_thread_term (&thread4);

    return 0;
}