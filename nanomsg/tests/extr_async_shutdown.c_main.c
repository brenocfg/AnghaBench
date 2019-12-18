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
 int /*<<< orphan*/  NN_PULL ; 
 int TEST_LOOPS ; 
 int /*<<< orphan*/  get_test_port (int,char const**) ; 
 int /*<<< orphan*/  nn_sleep (int) ; 
 int /*<<< orphan*/  nn_thread_init (struct nn_thread*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  nn_thread_term (struct nn_thread*) ; 
 int /*<<< orphan*/  routine ; 
 int /*<<< orphan*/  test_addr_from (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bind (int,char*) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main (int argc, const char *argv[])
{
    int sb;
    int i;
    struct nn_thread thread;
    char socket_address[128];

    test_addr_from(socket_address, "tcp", "127.0.0.1",
            get_test_port(argc, argv));

    for (i = 0; i != TEST_LOOPS; ++i) {
        sb = test_socket (AF_SP, NN_PULL);
        test_bind (sb, socket_address);
        nn_sleep (100);
        nn_thread_init (&thread, routine, &sb);
        nn_sleep (100);
        test_close (sb);
        nn_thread_term (&thread);
    }

    return 0;
}