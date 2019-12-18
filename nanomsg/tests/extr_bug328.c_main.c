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

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 int /*<<< orphan*/  NN_PAIR ; 
 int /*<<< orphan*/  NN_STAT_CURRENT_CONNECTIONS ; 
 int /*<<< orphan*/  get_test_port (int,char const**) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int nn_get_statistic (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_sleep (int) ; 
 int /*<<< orphan*/  test_addr_from (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bind (int,char*) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,char*) ; 
 int /*<<< orphan*/  test_recv (int,char*) ; 
 int /*<<< orphan*/  test_send (int,char*) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main (int argc, const char *argv[])
{
    int sb;
    int sc;
    char socket_address[128];

    test_addr_from(socket_address, "tcp", "127.0.0.1",
            get_test_port(argc, argv));

    sb = test_socket (AF_SP, NN_PAIR);
    test_bind (sb, socket_address);
    sc = test_socket (AF_SP, NN_PAIR);
    test_connect (sc, socket_address);

    nn_sleep(100);
    test_send (sc, "ABC");
    test_recv (sb, "ABC");
    nn_assert (nn_get_statistic (sc, NN_STAT_CURRENT_CONNECTIONS) == 1);
    test_close (sb);
    nn_sleep(300);
    nn_assert (nn_get_statistic (sc, NN_STAT_CURRENT_CONNECTIONS) == 0);
    test_close (sc);

    return 0;
}