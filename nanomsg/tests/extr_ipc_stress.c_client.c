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
 int /*<<< orphan*/  NN_PUSH ; 
 int /*<<< orphan*/  SOCKET_ADDRESS ; 
 int TEST_LOOPS ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_close (int) ; 
 scalar_t__ nn_connect (int,int /*<<< orphan*/ ) ; 
 int nn_send (int,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_sleep (int) ; 
 int nn_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static void client(void *arg)
{
    intptr_t id = (intptr_t)arg;
    int bytes;
    char msg[3];
    size_t sz_msg;
    int i;

    msg[0] = 'A' + id%26;
    msg[1] = 'a';
    msg[2] = '\0';
    /*  '\0' too */
    sz_msg = strlen (msg) + 1;

    for (i = 0; i < TEST_LOOPS; i++) {
        int cli_sock = nn_socket (AF_SP, NN_PUSH);
        msg[1] = 'a' + i%26;
        nn_assert (cli_sock >= 0);
        nn_assert (nn_connect (cli_sock, SOCKET_ADDRESS) >= 0);
        /*  Give time to allow for connect to establish. */
        nn_sleep (50);
        bytes = nn_send (cli_sock, msg, sz_msg, 0);
        /*  This would better be handled via semaphore or condvar. */
        nn_sleep (100);
        nn_assert ((size_t)bytes == sz_msg);
        nn_close (cli_sock);
    }
}