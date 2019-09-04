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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {scalar_t__ magic; int opcode; scalar_t__ datatype; scalar_t__ status; int opaque; scalar_t__ keylen; scalar_t__ extlen; int bodylen; scalar_t__ cas; } ;
struct TYPE_7__ {TYPE_1__ response; } ;
struct TYPE_8__ {TYPE_2__ header; } ;
struct TYPE_9__ {TYPE_3__ message; } ;
typedef  TYPE_4__ protocol_binary_response_no_extras ;

/* Variables and functions */
#define  PROTOCOL_BINARY_CMD_ADD 158 
#define  PROTOCOL_BINARY_CMD_ADDQ 157 
#define  PROTOCOL_BINARY_CMD_APPEND 156 
#define  PROTOCOL_BINARY_CMD_APPENDQ 155 
#define  PROTOCOL_BINARY_CMD_DECREMENT 154 
#define  PROTOCOL_BINARY_CMD_DECREMENTQ 153 
#define  PROTOCOL_BINARY_CMD_DELETE 152 
#define  PROTOCOL_BINARY_CMD_DELETEQ 151 
#define  PROTOCOL_BINARY_CMD_FLUSH 150 
#define  PROTOCOL_BINARY_CMD_FLUSHQ 149 
#define  PROTOCOL_BINARY_CMD_GAT 148 
#define  PROTOCOL_BINARY_CMD_GATK 147 
#define  PROTOCOL_BINARY_CMD_GATKQ 146 
#define  PROTOCOL_BINARY_CMD_GATQ 145 
#define  PROTOCOL_BINARY_CMD_GET 144 
#define  PROTOCOL_BINARY_CMD_GETK 143 
#define  PROTOCOL_BINARY_CMD_GETKQ 142 
#define  PROTOCOL_BINARY_CMD_GETQ 141 
#define  PROTOCOL_BINARY_CMD_INCREMENT 140 
#define  PROTOCOL_BINARY_CMD_INCREMENTQ 139 
#define  PROTOCOL_BINARY_CMD_NOOP 138 
#define  PROTOCOL_BINARY_CMD_PREPEND 137 
#define  PROTOCOL_BINARY_CMD_PREPENDQ 136 
#define  PROTOCOL_BINARY_CMD_QUIT 135 
#define  PROTOCOL_BINARY_CMD_QUITQ 134 
#define  PROTOCOL_BINARY_CMD_REPLACE 133 
#define  PROTOCOL_BINARY_CMD_REPLACEQ 132 
#define  PROTOCOL_BINARY_CMD_SET 131 
#define  PROTOCOL_BINARY_CMD_SETQ 130 
#define  PROTOCOL_BINARY_CMD_STAT 129 
#define  PROTOCOL_BINARY_CMD_VERSION 128 
 scalar_t__ PROTOCOL_BINARY_RAW_BYTES ; 
 scalar_t__ PROTOCOL_BINARY_RES ; 
 scalar_t__ PROTOCOL_BINARY_RESPONSE_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void validate_response_header(protocol_binary_response_no_extras *response,
                                     uint8_t cmd, uint16_t status)
{
    assert(response->message.header.response.magic == PROTOCOL_BINARY_RES);
    assert(response->message.header.response.opcode == cmd);
    assert(response->message.header.response.datatype == PROTOCOL_BINARY_RAW_BYTES);
    assert(response->message.header.response.status == status);
    assert(response->message.header.response.opaque == 0xdeadbeef);

    if (status == PROTOCOL_BINARY_RESPONSE_SUCCESS) {
        switch (cmd) {
        case PROTOCOL_BINARY_CMD_ADDQ:
        case PROTOCOL_BINARY_CMD_APPENDQ:
        case PROTOCOL_BINARY_CMD_DECREMENTQ:
        case PROTOCOL_BINARY_CMD_DELETEQ:
        case PROTOCOL_BINARY_CMD_FLUSHQ:
        case PROTOCOL_BINARY_CMD_INCREMENTQ:
        case PROTOCOL_BINARY_CMD_PREPENDQ:
        case PROTOCOL_BINARY_CMD_QUITQ:
        case PROTOCOL_BINARY_CMD_REPLACEQ:
        case PROTOCOL_BINARY_CMD_SETQ:
            assert("Quiet command shouldn't return on success" == NULL);
        default:
            break;
        }

        switch (cmd) {
        case PROTOCOL_BINARY_CMD_ADD:
        case PROTOCOL_BINARY_CMD_REPLACE:
        case PROTOCOL_BINARY_CMD_SET:
        case PROTOCOL_BINARY_CMD_APPEND:
        case PROTOCOL_BINARY_CMD_PREPEND:
            assert(response->message.header.response.keylen == 0);
            assert(response->message.header.response.extlen == 0);
            assert(response->message.header.response.bodylen == 0);
            assert(response->message.header.response.cas != 0);
            break;
        case PROTOCOL_BINARY_CMD_FLUSH:
        case PROTOCOL_BINARY_CMD_NOOP:
        case PROTOCOL_BINARY_CMD_QUIT:
        case PROTOCOL_BINARY_CMD_DELETE:
            assert(response->message.header.response.keylen == 0);
            assert(response->message.header.response.extlen == 0);
            assert(response->message.header.response.bodylen == 0);
            assert(response->message.header.response.cas == 0);
            break;

        case PROTOCOL_BINARY_CMD_DECREMENT:
        case PROTOCOL_BINARY_CMD_INCREMENT:
            assert(response->message.header.response.keylen == 0);
            assert(response->message.header.response.extlen == 0);
            assert(response->message.header.response.bodylen == 8);
            assert(response->message.header.response.cas != 0);
            break;

        case PROTOCOL_BINARY_CMD_STAT:
            assert(response->message.header.response.extlen == 0);
            /* key and value exists in all packets except in the terminating */
            assert(response->message.header.response.cas == 0);
            break;

        case PROTOCOL_BINARY_CMD_VERSION:
            assert(response->message.header.response.keylen == 0);
            assert(response->message.header.response.extlen == 0);
            assert(response->message.header.response.bodylen != 0);
            assert(response->message.header.response.cas == 0);
            break;

        case PROTOCOL_BINARY_CMD_GET:
        case PROTOCOL_BINARY_CMD_GETQ:
        case PROTOCOL_BINARY_CMD_GAT:
        case PROTOCOL_BINARY_CMD_GATQ:
            assert(response->message.header.response.keylen == 0);
            assert(response->message.header.response.extlen == 4);
            assert(response->message.header.response.cas != 0);
            break;

        case PROTOCOL_BINARY_CMD_GETK:
        case PROTOCOL_BINARY_CMD_GETKQ:
        case PROTOCOL_BINARY_CMD_GATK:
        case PROTOCOL_BINARY_CMD_GATKQ:
            assert(response->message.header.response.keylen != 0);
            assert(response->message.header.response.extlen == 4);
            assert(response->message.header.response.cas != 0);
            break;

        default:
            /* Undefined command code */
            break;
        }
    } else {
        assert(response->message.header.response.cas == 0);
        assert(response->message.header.response.extlen == 0);
        if (cmd != PROTOCOL_BINARY_CMD_GETK &&
            cmd != PROTOCOL_BINARY_CMD_GATK) {
            assert(response->message.header.response.keylen == 0);
        }
    }
}