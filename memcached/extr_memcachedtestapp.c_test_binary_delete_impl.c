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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  protocol_binary_response_no_extras ;
typedef  int /*<<< orphan*/  protocol_binary_request_no_extras ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;

/* Variables and functions */
 scalar_t__ PROTOCOL_BINARY_CMD_ADD ; 
 scalar_t__ PROTOCOL_BINARY_CMD_DELETE ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_KEY_ENOENT ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_SUCCESS ; 
 int TEST_PASS ; 
 size_t raw_command (char*,int,scalar_t__,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_recv_packet (char*,int) ; 
 int /*<<< orphan*/  safe_send (char*,size_t,int) ; 
 size_t storage_command (char*,int,scalar_t__,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  validate_response_header (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum test_return test_binary_delete_impl(const char *key, uint8_t cmd) {
    union {
        protocol_binary_request_no_extras request;
        protocol_binary_response_no_extras response;
        char bytes[1024];
    } send, receive;
    size_t len = raw_command(send.bytes, sizeof(send.bytes), cmd,
                             key, strlen(key), NULL, 0);

    safe_send(send.bytes, len, false);
    safe_recv_packet(receive.bytes, sizeof(receive.bytes));
    validate_response_header(&receive.response, cmd,
                             PROTOCOL_BINARY_RESPONSE_KEY_ENOENT);
    len = storage_command(send.bytes, sizeof(send.bytes),
                          PROTOCOL_BINARY_CMD_ADD,
                          key, strlen(key), NULL, 0, 0, 0);
    safe_send(send.bytes, len, false);
    safe_recv_packet(receive.bytes, sizeof(receive.bytes));
    validate_response_header(&receive.response, PROTOCOL_BINARY_CMD_ADD,
                             PROTOCOL_BINARY_RESPONSE_SUCCESS);

    len = raw_command(send.bytes, sizeof(send.bytes),
                      cmd, key, strlen(key), NULL, 0);
    safe_send(send.bytes, len, false);

    if (cmd == PROTOCOL_BINARY_CMD_DELETE) {
        safe_recv_packet(receive.bytes, sizeof(receive.bytes));
        validate_response_header(&receive.response, PROTOCOL_BINARY_CMD_DELETE,
                                 PROTOCOL_BINARY_RESPONSE_SUCCESS);
    }

    safe_send(send.bytes, len, false);
    safe_recv_packet(receive.bytes, sizeof(receive.bytes));
    validate_response_header(&receive.response, cmd,
                             PROTOCOL_BINARY_RESPONSE_KEY_ENOENT);

    return TEST_PASS;
}