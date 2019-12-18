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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  in_port_t ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;

/* Variables and functions */
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGTERM ; 
 int TEST_PASS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  start_server (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static enum test_return test_issue_44(void) {
    in_port_t port;
    pid_t pid = start_server(&port, true, 15);
    assert(kill(pid, SIGHUP) == 0);
    sleep(1);
    assert(kill(pid, SIGTERM) == 0);

    return TEST_PASS;
}