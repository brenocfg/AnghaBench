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
 int /*<<< orphan*/  NN_REQ ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int /*<<< orphan*/  get_test_port (int,char const**) ; 
 int nn_shutdown (int,int) ; 
 int /*<<< orphan*/  test_addr_from (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int test_connect (int,char*) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main (int argc, const char *argv[])
{
    int s;
    int rc;
    int eid;
    char socket_address[128];

    test_addr_from(socket_address, "tcp", "127.0.0.1",
            get_test_port(argc, argv));

    /*  Run endpoint shutdown and socket shutdown in parallel. */
    s = test_socket (AF_SP, NN_REQ);
    eid = test_connect (s, socket_address);
    rc = nn_shutdown (s, eid);
    errno_assert (rc == 0);
    test_close (s);

    return 0;
}