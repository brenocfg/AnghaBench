#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rsp ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_5__ {scalar_t__ (* read ) (TYPE_1__*,char*,int) ;} ;

/* Variables and functions */
 int TEST_PASS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close_conn () ; 
 TYPE_1__* con ; 
 TYPE_1__* connect_server (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_ssl ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  read_ascii_response (char*,int) ; 
 int /*<<< orphan*/  send_ascii_command (char*) ; 
 size_t snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_1__*,char*,int) ; 
 scalar_t__ stub2 (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static enum test_return test_issue_102(void) {
    char buffer[4096];
    memset(buffer, ' ', sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    close_conn();
    con = connect_server("127.0.0.1", port, false, enable_ssl);

    send_ascii_command(buffer);
    /* verify that the server closed the connection */
    assert(con->read(con, buffer, sizeof(buffer)) == 0);

    con = connect_server("127.0.0.1", port, false, enable_ssl);

    snprintf(buffer, sizeof(buffer), "gets ");
    size_t offset = 5;
    while (offset < 4000) {
        offset += snprintf(buffer + offset, sizeof(buffer) - offset,
                           "%010u ", (unsigned int)offset);
    }

    send_ascii_command(buffer);
    usleep(250);

    send_ascii_command("\r\n");
    char rsp[80];
    read_ascii_response(rsp, sizeof(rsp));
    assert(strncmp(rsp, "END", strlen("END")) == 0);
    buffer[3]= ' ';
    send_ascii_command(buffer);
    usleep(250);
    send_ascii_command("\r\n");
    read_ascii_response(rsp, sizeof(rsp));
    assert(strncmp(rsp, "END", strlen("END")) == 0);

    memset(buffer, ' ', sizeof(buffer));
    int len = snprintf(buffer + 101, sizeof(buffer) - 101, "gets foo");
    buffer[101 + len] = ' ';
    buffer[sizeof(buffer) - 1] = '\0';
    send_ascii_command(buffer);
    /* verify that the server closed the connection */
    assert(con->read(con, buffer, sizeof(buffer)) == 0);

    close_conn();
    con = connect_server("127.0.0.1", port, false, enable_ssl);

    return TEST_PASS;
}