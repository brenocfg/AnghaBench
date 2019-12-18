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
typedef  int /*<<< orphan*/  sndtimeo ;
typedef  int /*<<< orphan*/  rcvtimeo ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 int /*<<< orphan*/  NN_PUB ; 
 int /*<<< orphan*/  NN_RCVTIMEO ; 
 int /*<<< orphan*/  NN_SNDTIMEO ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  NN_SUB ; 
 int /*<<< orphan*/  NN_SUB_SUBSCRIBE ; 
 int TEST_LOOPS ; 
 int TEST_THREADS ; 
 int /*<<< orphan*/  get_test_port (int,char const**) ; 
 int /*<<< orphan*/  nn_sleep (int) ; 
 int /*<<< orphan*/  nn_thread_init (struct nn_thread*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  nn_thread_term (struct nn_thread*) ; 
 int /*<<< orphan*/  routine ; 
 int /*<<< orphan*/  socket_address ; 
 int /*<<< orphan*/  test_addr_from (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bind (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_send (int,char*) ; 
 int /*<<< orphan*/  test_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main (int argc, const char *argv[])
{
    int i;
    int j;
    int s;
    int sb;
    int rcvtimeo = 10;
    int sndtimeo = 0;
    int sockets [TEST_THREADS];
    struct nn_thread threads [TEST_THREADS];

    test_addr_from (socket_address, "ws", "127.0.0.1",
        get_test_port (argc, argv));

    for (i = 0; i != TEST_LOOPS; ++i) {

        sb = test_socket (AF_SP, NN_PUB);
        test_bind (sb, socket_address);
        test_setsockopt (sb, NN_SOL_SOCKET, NN_SNDTIMEO,
            &sndtimeo, sizeof (sndtimeo));

        for (j = 0; j < TEST_THREADS; j++){
            s = test_socket (AF_SP, NN_SUB);
            test_setsockopt (s, NN_SOL_SOCKET, NN_RCVTIMEO,
                &rcvtimeo, sizeof (rcvtimeo));
            test_setsockopt (s, NN_SUB, NN_SUB_SUBSCRIBE, "", 0);
            test_connect (s, socket_address);
            sockets [j] = s;
            nn_thread_init (&threads [j], routine, &sockets [j]);
        }

        /*  Allow all threads a bit of time to connect. */
        nn_sleep (100);

        test_send (sb, "");

        for (j = 0; j < TEST_THREADS; j++) {
            test_close (sockets [j]);
            nn_thread_term (&threads [j]);
        }

        test_close (sb);
    }

    return 0;
}