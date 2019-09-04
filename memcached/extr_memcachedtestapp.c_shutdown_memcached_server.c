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
typedef  enum test_return { ____Placeholder_test_return } test_return ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_4__ {scalar_t__ (* read ) (TYPE_1__*,char*,int) ;} ;

/* Variables and functions */
 int TEST_PASS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close_conn () ; 
 TYPE_1__* con ; 
 TYPE_1__* connect_server (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_ssl ; 
 scalar_t__ kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  send_ascii_command (char*) ; 
 int server_pid ; 
 scalar_t__ stub1 (TYPE_1__*,char*,int) ; 

__attribute__((used)) static enum test_return shutdown_memcached_server(void) {
    char buffer[1024];

    close_conn();
    con = connect_server("127.0.0.1", port, false, enable_ssl);

    send_ascii_command("shutdown\r\n");
    /* verify that the server closed the connection */
    assert(con->read(con, buffer, sizeof(buffer)) == 0);

    close_conn();

    /* We set server_pid to -1 so that we don't later call kill() */
    if (kill(server_pid, 0) == 0) {
        server_pid = -1;
    }

    return TEST_PASS;
}