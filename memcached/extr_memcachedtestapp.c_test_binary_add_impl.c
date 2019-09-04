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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  protocol_binary_response_no_extras ;
typedef  int /*<<< orphan*/  protocol_binary_request_no_extras ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_CMD_ADD ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_KEY_EEXISTS ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_SUCCESS ; 
 int TEST_PASS ; 
 int /*<<< orphan*/  safe_recv_packet (char*,int) ; 
 int /*<<< orphan*/  safe_send (char*,size_t,int) ; 
 size_t storage_command (char*,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  validate_response_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum test_return test_binary_add_impl(const char *key, uint8_t cmd) {
    uint64_t value = 0xdeadbeefdeadcafe;
    union {
        protocol_binary_request_no_extras request;
        protocol_binary_response_no_extras response;
        char bytes[1024];
    } send, receive;
    size_t len = storage_command(send.bytes, sizeof(send.bytes), cmd, key,
                                 strlen(key), &value, sizeof(value),
                                 0, 0);

    /* Add should only work the first time */
    int ii;
    for (ii = 0; ii < 10; ++ii) {
        safe_send(send.bytes, len, false);
        if (ii == 0) {
            if (cmd == PROTOCOL_BINARY_CMD_ADD) {
                safe_recv_packet(receive.bytes, sizeof(receive.bytes));
                validate_response_header(&receive.response, cmd,
                                         PROTOCOL_BINARY_RESPONSE_SUCCESS);
            }
        } else {
            safe_recv_packet(receive.bytes, sizeof(receive.bytes));
            validate_response_header(&receive.response, cmd,
                                     PROTOCOL_BINARY_RESPONSE_KEY_EEXISTS);
        }
    }

    return TEST_PASS;
}