#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  protocol_binary_response_no_extras ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {TYPE_1__ body; } ;
struct TYPE_6__ {TYPE_2__ message; } ;
typedef  TYPE_3__ protocol_binary_response_decr ;
typedef  int /*<<< orphan*/  protocol_binary_request_no_extras ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_CMD_DECREMENT ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_SUCCESS ; 
 int TEST_PASS ; 
 size_t arithmetic_command (char*,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int ntohll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_recv_packet (char*,int) ; 
 int /*<<< orphan*/  safe_send (char*,size_t,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  test_binary_noop () ; 
 int /*<<< orphan*/  validate_response_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum test_return test_binary_decr_impl(const char* key, uint8_t cmd) {
    union {
        protocol_binary_request_no_extras request;
        protocol_binary_response_no_extras response_header;
        protocol_binary_response_decr response;
        char bytes[1024];
    } send, receive;
    size_t len = arithmetic_command(send.bytes, sizeof(send.bytes), cmd,
                                    key, strlen(key), 1, 9, 0);

    int ii;
    for (ii = 9; ii >= 0; --ii) {
        safe_send(send.bytes, len, false);
        if (cmd == PROTOCOL_BINARY_CMD_DECREMENT) {
            safe_recv_packet(receive.bytes, sizeof(receive.bytes));
            validate_response_header(&receive.response_header, cmd,
                                     PROTOCOL_BINARY_RESPONSE_SUCCESS);
            assert(ntohll(receive.response.message.body.value) == ii);
        }
    }

    /* decr on 0 should not wrap */
    safe_send(send.bytes, len, false);
    if (cmd == PROTOCOL_BINARY_CMD_DECREMENT) {
        safe_recv_packet(receive.bytes, sizeof(receive.bytes));
        validate_response_header(&receive.response_header, cmd,
                                 PROTOCOL_BINARY_RESPONSE_SUCCESS);
        assert(ntohll(receive.response.message.body.value) == 0);
    } else {
        test_binary_noop();
    }

    return TEST_PASS;
}