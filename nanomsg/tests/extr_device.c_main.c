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

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  NN_BUS ; 
 int /*<<< orphan*/  NN_PAIR ; 
 int /*<<< orphan*/  NN_PULL ; 
 int /*<<< orphan*/  NN_PUSH ; 
 int /*<<< orphan*/  NN_RCVTIMEO ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  SOCKET_ADDRESS_A ; 
 int /*<<< orphan*/  SOCKET_ADDRESS_B ; 
 int /*<<< orphan*/  SOCKET_ADDRESS_C ; 
 int /*<<< orphan*/  SOCKET_ADDRESS_D ; 
 int /*<<< orphan*/  SOCKET_ADDRESS_E ; 
 int /*<<< orphan*/  device1 ; 
 int /*<<< orphan*/  device2 ; 
 int /*<<< orphan*/  device3 ; 
 int /*<<< orphan*/  nn_sleep (int) ; 
 int /*<<< orphan*/  nn_term () ; 
 int /*<<< orphan*/  nn_thread_init (struct nn_thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_thread_term (struct nn_thread*) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_drop (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_recv (int,char*) ; 
 int /*<<< orphan*/  test_send (int,char*) ; 
 int /*<<< orphan*/  test_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main ()
{
    int enda;
    int endb;
    int endc;
    int endd;
    int ende1;
    int ende2;
    struct nn_thread thread1;
    struct nn_thread thread2;
    struct nn_thread thread3;
    int timeo;

    /*  Test the bi-directional device. */

    /*  Start the device. */
    nn_thread_init (&thread1, device1, NULL);

    /*  Create two sockets to connect to the device. */
    enda = test_socket (AF_SP, NN_PAIR);
    test_connect (enda, SOCKET_ADDRESS_A);
    endb = test_socket (AF_SP, NN_PAIR);
    test_connect (endb, SOCKET_ADDRESS_B);

    /*  Pass a pair of messages between endpoints. */
    test_send (enda, "ABC");
    test_recv (endb, "ABC");
    test_send (endb, "ABC");
    test_recv (enda, "ABC");

    /*  Clean up. */
    test_close (endb);
    test_close (enda);

    /*  Test the uni-directional device. */

    /*  Start the device. */
    nn_thread_init (&thread2, device2, NULL);

    /*  Create two sockets to connect to the device. */
    endc = test_socket (AF_SP, NN_PUSH);
    test_connect (endc, SOCKET_ADDRESS_C);
    endd = test_socket (AF_SP, NN_PULL);
    test_connect (endd, SOCKET_ADDRESS_D);

    /*  Pass a message between endpoints. */
    test_send (endc, "XYZ");
    test_recv (endd, "XYZ");

    /*  Clean up. */
    test_close (endd);
    test_close (endc);

    /*  Test the loopback device. */

    /*  Start the device. */
    nn_thread_init (&thread3, device3, NULL);

    /*  Create two sockets to connect to the device. */
    ende1 = test_socket (AF_SP, NN_BUS);
    test_connect (ende1, SOCKET_ADDRESS_E);
    ende2 = test_socket (AF_SP, NN_BUS);
    test_connect (ende2, SOCKET_ADDRESS_E);

    /*  BUS is unreliable so wait a bit for connections to be established. */
    nn_sleep (100);

    /*  Pass a message to the bus. */
    test_send (ende1, "KLM");
    test_recv (ende2, "KLM");

    /*  Make sure that the message doesn't arrive at the socket it was
        originally sent to. */
    timeo = 100;
    test_setsockopt (ende1, NN_SOL_SOCKET, NN_RCVTIMEO,
       &timeo, sizeof (timeo));
    test_drop (ende1, ETIMEDOUT);

    /*  Clean up. */
    test_close (ende2);
    test_close (ende1);

    /*  Shut down the devices. */
    nn_term ();
    nn_thread_term (&thread1);
    nn_thread_term (&thread2);
    nn_thread_term (&thread3);

    return 0;
}