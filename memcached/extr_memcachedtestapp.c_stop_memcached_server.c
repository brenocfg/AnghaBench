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
typedef  enum test_return { ____Placeholder_test_return } test_return ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int TEST_PASS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close_conn () ; 
 scalar_t__ kill (int,int /*<<< orphan*/ ) ; 
 int server_pid ; 

__attribute__((used)) static enum test_return stop_memcached_server(void) {
    close_conn();
    if (server_pid != -1) {
        assert(kill(server_pid, SIGTERM) == 0);
    }

    return TEST_PASS;
}