#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nn_thread {int dummy; } ;
typedef  int /*<<< orphan*/  ms ;
struct TYPE_4__ {scalar_t__ n; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 int /*<<< orphan*/  NN_PUB ; 
 int /*<<< orphan*/  NN_PUSH ; 
 int /*<<< orphan*/  NN_SNDTIMEO ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int TEST2_THREAD_COUNT ; 
 int TEST_LOOPS ; 
 int THREAD_COUNT ; 
 TYPE_1__ active ; 
 int /*<<< orphan*/  get_test_port (int,char const**) ; 
 int /*<<< orphan*/  nn_atomic_init (TYPE_1__*,int) ; 
 int /*<<< orphan*/  nn_atomic_term (TYPE_1__*) ; 
 int /*<<< orphan*/  nn_send (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_sleep (int) ; 
 int /*<<< orphan*/  nn_thread_init (struct nn_thread*,int /*<<< orphan*/ ,struct nn_thread*) ; 
 int /*<<< orphan*/  nn_thread_term (struct nn_thread*) ; 
 int /*<<< orphan*/  routine ; 
 int /*<<< orphan*/  routine2 ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_address ; 
 int /*<<< orphan*/  test_addr_from (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bind (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main (int argc, const char *argv[])
{
    int sb;
    int i;
    int j;
    struct nn_thread threads [THREAD_COUNT];

    test_addr_from(socket_address, "tcp", "127.0.0.1",
            get_test_port(argc, argv));

    /*  Stress the shutdown algorithm. */

#if defined(SIGPIPE) && defined(SIG_IGN)
    signal (SIGPIPE, SIG_IGN);
#endif

    sb = test_socket (AF_SP, NN_PUB);
    test_bind (sb, socket_address);

    for (j = 0; j != TEST_LOOPS; ++j) {
        for (i = 0; i != THREAD_COUNT; ++i)
            nn_thread_init (&threads [i], routine, NULL);
        for (i = 0; i != THREAD_COUNT; ++i) {
            nn_thread_term (&threads [i]);
	}
    }

    test_close (sb);

    /*  Test race condition of sending message while socket shutting down  */

    sb = test_socket (AF_SP, NN_PUSH);
    test_bind (sb, socket_address);

    for (j = 0; j != TEST_LOOPS; ++j) {
	int ms;
        nn_atomic_init(&active, TEST2_THREAD_COUNT);
        for (i = 0; i != TEST2_THREAD_COUNT; ++i)
            nn_thread_init (&threads [i], routine2, &threads[i]);

	nn_sleep(100);
	ms = 200;
	test_setsockopt (sb, NN_SOL_SOCKET, NN_SNDTIMEO, &ms, sizeof (ms));
        while (active.n) {
            (void) nn_send (sb, "hello", 5, 0);
        }

        for (i = 0; i != TEST2_THREAD_COUNT; ++i)
            nn_thread_term (&threads [i]);
        nn_atomic_term(&active);
    }

    test_close (sb);

    return 0;
}