#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int keylen; int bodylen; } ;
struct TYPE_7__ {TYPE_1__ response; } ;
struct TYPE_8__ {TYPE_2__ header; } ;
struct TYPE_9__ {TYPE_3__ message; } ;
typedef  TYPE_4__ protocol_binary_response_no_extras ;
typedef  int /*<<< orphan*/  protocol_binary_request_no_extras ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_CMD_ADD ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_CMD_APPEND ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_CMD_GETK ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_CMD_NOOP ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_CMD_PREPEND ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_NOT_STORED ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_SUCCESS ; 
 int TEST_PASS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 size_t raw_command (char*,int,int /*<<< orphan*/ ,char const*,int,char const*,int) ; 
 int /*<<< orphan*/  safe_recv_packet (char*,int) ; 
 int /*<<< orphan*/  safe_send (char*,size_t,int) ; 
 size_t storage_command (char*,int,int /*<<< orphan*/ ,char const*,int,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  validate_response_header (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum test_return test_binary_concat_impl(const char *key, uint8_t cmd) {
    union {
        protocol_binary_request_no_extras request;
        protocol_binary_response_no_extras response;
        char bytes[1024];
    } send, receive;
    const char *value = "world";

    size_t len = raw_command(send.bytes, sizeof(send.bytes), cmd,
                              key, strlen(key), value, strlen(value));


    safe_send(send.bytes, len, false);
    safe_recv_packet(receive.bytes, sizeof(receive.bytes));
    validate_response_header(&receive.response, cmd,
                             PROTOCOL_BINARY_RESPONSE_NOT_STORED);

    len = storage_command(send.bytes, sizeof(send.bytes),
                          PROTOCOL_BINARY_CMD_ADD,
                          key, strlen(key), value, strlen(value), 0, 0);
    safe_send(send.bytes, len, false);
    safe_recv_packet(receive.bytes, sizeof(receive.bytes));
    validate_response_header(&receive.response, PROTOCOL_BINARY_CMD_ADD,
                             PROTOCOL_BINARY_RESPONSE_SUCCESS);

    len = raw_command(send.bytes, sizeof(send.bytes), cmd,
                      key, strlen(key), value, strlen(value));
    safe_send(send.bytes, len, false);

    if (cmd == PROTOCOL_BINARY_CMD_APPEND || cmd == PROTOCOL_BINARY_CMD_PREPEND) {
        safe_recv_packet(receive.bytes, sizeof(receive.bytes));
        validate_response_header(&receive.response, cmd,
                                 PROTOCOL_BINARY_RESPONSE_SUCCESS);
    } else {
        len = raw_command(send.bytes, sizeof(send.bytes), PROTOCOL_BINARY_CMD_NOOP,
                          NULL, 0, NULL, 0);
        safe_send(send.bytes, len, false);
        safe_recv_packet(receive.bytes, sizeof(receive.bytes));
        validate_response_header(&receive.response, PROTOCOL_BINARY_CMD_NOOP,
                                 PROTOCOL_BINARY_RESPONSE_SUCCESS);
    }

    len = raw_command(send.bytes, sizeof(send.bytes), PROTOCOL_BINARY_CMD_GETK,
                      key, strlen(key), NULL, 0);

    safe_send(send.bytes, len, false);
    safe_recv_packet(receive.bytes, sizeof(receive.bytes));
    validate_response_header(&receive.response, PROTOCOL_BINARY_CMD_GETK,
                             PROTOCOL_BINARY_RESPONSE_SUCCESS);

    assert(receive.response.message.header.response.keylen == strlen(key));
    assert(receive.response.message.header.response.bodylen == (strlen(key) + 2*strlen(value) + 4));

    char *ptr = receive.bytes;
    ptr += sizeof(receive.response);
    ptr += 4;

    assert(memcmp(ptr, key, strlen(key)) == 0);
    ptr += strlen(key);
    assert(memcmp(ptr, value, strlen(value)) == 0);
    ptr += strlen(value);
    assert(memcmp(ptr, value, strlen(value)) == 0);

    return TEST_PASS;
}