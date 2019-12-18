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
 int TEST_PASS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_conn () ; 
 int /*<<< orphan*/  con ; 
 int /*<<< orphan*/  connect_server (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_ssl ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  server_pid ; 
 int /*<<< orphan*/  start_server (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static enum test_return start_memcached_server(void) {
    server_pid = start_server(&port, false, 600);
    close_conn();
    con = connect_server("127.0.0.1", port, false, enable_ssl);
    assert(con);
    return TEST_PASS;
}