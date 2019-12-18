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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int TEST_PASS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close_conn () ; 
 int con ; 
 int connect_server (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_ssl ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  read_ascii_response (char*,int) ; 
 int /*<<< orphan*/  send_ascii_command (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum test_return test_issue_92(void) {
    char buffer[1024];

    close_conn();
    con = connect_server("127.0.0.1", port, false, enable_ssl);
    assert(con);

    send_ascii_command("stats cachedump 1 0 0\r\n");

    read_ascii_response(buffer, sizeof(buffer));
    assert(strncmp(buffer, "END", strlen("END")) == 0);

    send_ascii_command("stats cachedump 200 0 0\r\n");
    read_ascii_response(buffer, sizeof(buffer));
    assert(strncmp(buffer, "CLIENT_ERROR", strlen("CLIENT_ERROR")) == 0);

    close_conn();
    con = connect_server("127.0.0.1", port, false, enable_ssl);
    assert(con);
    return TEST_PASS;
}