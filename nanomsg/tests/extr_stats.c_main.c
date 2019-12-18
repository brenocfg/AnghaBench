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
 int /*<<< orphan*/  NN_REP ; 
 int /*<<< orphan*/  NN_REQ ; 
 int /*<<< orphan*/  NN_STAT_ACCEPTED_CONNECTIONS ; 
 int /*<<< orphan*/  NN_STAT_BYTES_RECEIVED ; 
 int /*<<< orphan*/  NN_STAT_BYTES_SENT ; 
 int /*<<< orphan*/  NN_STAT_CURRENT_CONNECTIONS ; 
 int /*<<< orphan*/  NN_STAT_ESTABLISHED_CONNECTIONS ; 
 int /*<<< orphan*/  NN_STAT_MESSAGES_RECEIVED ; 
 int /*<<< orphan*/  NN_STAT_MESSAGES_SENT ; 
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
    int rep1;
    int req1;
    char socket_address[128];

    test_addr_from(socket_address, "tcp", "127.0.0.1",
            get_test_port(argc, argv));

    /*  Test req/rep with full socket types. */
    rep1 = test_socket (AF_SP, NN_REP);
    test_bind (rep1, socket_address);
    nn_sleep (100);

    req1 = test_socket (AF_SP, NN_REQ);
    test_connect (req1, socket_address);
    nn_sleep (200);

    nn_assert (nn_get_statistic(rep1, NN_STAT_ACCEPTED_CONNECTIONS) == 1);
    nn_assert (nn_get_statistic(rep1, NN_STAT_ESTABLISHED_CONNECTIONS) == 0);
    nn_assert (nn_get_statistic(rep1, NN_STAT_CURRENT_CONNECTIONS) == 1);
    nn_assert (nn_get_statistic(rep1, NN_STAT_MESSAGES_SENT) == 0);
    nn_assert (nn_get_statistic(rep1, NN_STAT_MESSAGES_RECEIVED) == 0);

    nn_assert (nn_get_statistic(req1, NN_STAT_ACCEPTED_CONNECTIONS) == 0);
    nn_assert (nn_get_statistic(req1, NN_STAT_ESTABLISHED_CONNECTIONS) == 1);
    nn_assert (nn_get_statistic(req1, NN_STAT_CURRENT_CONNECTIONS) == 1);
    nn_assert (nn_get_statistic(req1, NN_STAT_MESSAGES_SENT) == 0);
    nn_assert (nn_get_statistic(req1, NN_STAT_MESSAGES_RECEIVED) == 0);

    test_send (req1, "ABC");
    nn_sleep (100);

    nn_assert (nn_get_statistic(req1, NN_STAT_MESSAGES_SENT) == 1);
    nn_assert (nn_get_statistic(req1, NN_STAT_BYTES_SENT) == 3);
    nn_assert (nn_get_statistic(req1, NN_STAT_MESSAGES_RECEIVED) == 0);
    nn_assert (nn_get_statistic(req1, NN_STAT_BYTES_RECEIVED) == 0);

    test_recv(rep1, "ABC");

    nn_assert (nn_get_statistic(rep1, NN_STAT_MESSAGES_SENT) == 0);
    nn_assert (nn_get_statistic(rep1, NN_STAT_BYTES_SENT) == 0);
    nn_assert (nn_get_statistic(rep1, NN_STAT_MESSAGES_RECEIVED) == 1);
    nn_assert (nn_get_statistic(rep1, NN_STAT_BYTES_RECEIVED) == 3);

    test_send (rep1, "OK");
    test_recv (req1, "OK");

    nn_assert (nn_get_statistic(req1, NN_STAT_MESSAGES_SENT) == 1);
    nn_assert (nn_get_statistic(req1, NN_STAT_BYTES_SENT) == 3);
    nn_assert (nn_get_statistic(req1, NN_STAT_MESSAGES_RECEIVED) == 1);
    nn_assert (nn_get_statistic(req1, NN_STAT_BYTES_RECEIVED) == 2);

    nn_assert (nn_get_statistic(rep1, NN_STAT_MESSAGES_SENT) == 1);
    nn_assert (nn_get_statistic(rep1, NN_STAT_BYTES_SENT) == 2);
    nn_assert (nn_get_statistic(rep1, NN_STAT_MESSAGES_RECEIVED) == 1);
    nn_assert (nn_get_statistic(rep1, NN_STAT_BYTES_RECEIVED) == 3);

    test_close (req1);

    nn_sleep (100);

    nn_assert (nn_get_statistic(rep1, NN_STAT_ACCEPTED_CONNECTIONS) == 1);
    nn_assert (nn_get_statistic(rep1, NN_STAT_ESTABLISHED_CONNECTIONS) == 0);
    nn_assert (nn_get_statistic(rep1, NN_STAT_CURRENT_CONNECTIONS) == 0);

    test_close (rep1);

    return 0;
}