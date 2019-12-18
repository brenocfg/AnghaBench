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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  protocol_binary_response_no_extras ;
typedef  int /*<<< orphan*/  protocol_binary_request_no_extras ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_UNKNOWN_COMMAND ; 
 int TEST_PASS ; 
 size_t raw_command (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_recv_packet (char*,int) ; 
 int /*<<< orphan*/  safe_send (char*,size_t,int) ; 
 int /*<<< orphan*/  validate_response_header (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum test_return test_binary_illegal(void) {
    uint8_t cmd = 0x25;
    while (cmd != 0x00) {
        union {
            protocol_binary_request_no_extras request;
            protocol_binary_response_no_extras response;
            char bytes[1024];
        } buffer;
        size_t len = raw_command(buffer.bytes, sizeof(buffer.bytes),
                                 cmd, NULL, 0, NULL, 0);
        safe_send(buffer.bytes, len, false);
        safe_recv_packet(buffer.bytes, sizeof(buffer.bytes));
        validate_response_header(&buffer.response, cmd,
                                 PROTOCOL_BINARY_RESPONSE_UNKNOWN_COMMAND);
        ++cmd;
    }

    return TEST_PASS;
}