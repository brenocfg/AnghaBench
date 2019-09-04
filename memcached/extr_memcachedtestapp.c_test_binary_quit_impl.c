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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  protocol_binary_response_no_extras ;
typedef  int /*<<< orphan*/  protocol_binary_request_no_extras ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;
struct TYPE_4__ {scalar_t__ (* read ) (TYPE_1__*,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_CMD_QUIT ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_SUCCESS ; 
 int TEST_PASS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close_conn () ; 
 TYPE_1__* con ; 
 TYPE_1__* connect_server (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_ssl ; 
 int /*<<< orphan*/  port ; 
 size_t raw_command (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_recv_packet (char*,int) ; 
 int /*<<< orphan*/  safe_send (char*,size_t,int) ; 
 scalar_t__ stub1 (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  validate_response_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum test_return test_binary_quit_impl(uint8_t cmd) {
    union {
        protocol_binary_request_no_extras request;
        protocol_binary_response_no_extras response;
        char bytes[1024];
    } buffer;
    size_t len = raw_command(buffer.bytes, sizeof(buffer.bytes),
                             cmd, NULL, 0, NULL, 0);

    safe_send(buffer.bytes, len, false);
    if (cmd == PROTOCOL_BINARY_CMD_QUIT) {
        safe_recv_packet(buffer.bytes, sizeof(buffer.bytes));
        validate_response_header(&buffer.response, PROTOCOL_BINARY_CMD_QUIT,
                                 PROTOCOL_BINARY_RESPONSE_SUCCESS);
    }

    /* Socket should be closed now, read should return 0 */
    assert(con->read(con, buffer.bytes, sizeof(buffer.bytes)) == 0);
    close_conn();
    con = connect_server("127.0.0.1", port, false, enable_ssl);

    return TEST_PASS;
}