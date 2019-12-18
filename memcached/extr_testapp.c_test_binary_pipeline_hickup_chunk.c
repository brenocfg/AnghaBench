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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  protocol_binary_request_no_extras ;
typedef  int off_t ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;

/* Variables and functions */
#define  PROTOCOL_BINARY_CMD_ADD 162 
#define  PROTOCOL_BINARY_CMD_ADDQ 161 
#define  PROTOCOL_BINARY_CMD_APPEND 160 
#define  PROTOCOL_BINARY_CMD_APPENDQ 159 
#define  PROTOCOL_BINARY_CMD_DECREMENT 158 
#define  PROTOCOL_BINARY_CMD_DECREMENTQ 157 
#define  PROTOCOL_BINARY_CMD_DELETE 156 
#define  PROTOCOL_BINARY_CMD_DELETEQ 155 
#define  PROTOCOL_BINARY_CMD_FLUSH 154 
#define  PROTOCOL_BINARY_CMD_FLUSHQ 153 
#define  PROTOCOL_BINARY_CMD_GAT 152 
#define  PROTOCOL_BINARY_CMD_GATK 151 
#define  PROTOCOL_BINARY_CMD_GATKQ 150 
#define  PROTOCOL_BINARY_CMD_GATQ 149 
#define  PROTOCOL_BINARY_CMD_GET 148 
#define  PROTOCOL_BINARY_CMD_GETK 147 
#define  PROTOCOL_BINARY_CMD_GETKQ 146 
#define  PROTOCOL_BINARY_CMD_GETQ 145 
#define  PROTOCOL_BINARY_CMD_INCREMENT 144 
#define  PROTOCOL_BINARY_CMD_INCREMENTQ 143 
#define  PROTOCOL_BINARY_CMD_NOOP 142 
#define  PROTOCOL_BINARY_CMD_PREPEND 141 
#define  PROTOCOL_BINARY_CMD_PREPENDQ 140 
#define  PROTOCOL_BINARY_CMD_QUIT 139 
#define  PROTOCOL_BINARY_CMD_QUITQ 138 
#define  PROTOCOL_BINARY_CMD_REPLACE 137 
#define  PROTOCOL_BINARY_CMD_REPLACEQ 136 
#define  PROTOCOL_BINARY_CMD_SASL_AUTH 135 
#define  PROTOCOL_BINARY_CMD_SASL_LIST_MECHS 134 
#define  PROTOCOL_BINARY_CMD_SASL_STEP 133 
#define  PROTOCOL_BINARY_CMD_SET 132 
#define  PROTOCOL_BINARY_CMD_SETQ 131 
#define  PROTOCOL_BINARY_CMD_STAT 130 
#define  PROTOCOL_BINARY_CMD_TOUCH 129 
#define  PROTOCOL_BINARY_CMD_VERSION 128 
 int TEST_PASS ; 
 size_t arithmetic_command (char*,int,int,char**,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hickup_thread_running ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int rand () ; 
 size_t raw_command (char*,int,int const,char**,size_t,int*,int) ; 
 int /*<<< orphan*/  safe_send (void*,int,int) ; 
 size_t storage_command (char*,int,int,char**,size_t,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t touch_command (char*,int,int,char**,size_t,int) ; 

__attribute__((used)) static enum test_return test_binary_pipeline_hickup_chunk(void *buffer, size_t buffersize) {
    off_t offset = 0;
    char *key[256];
    uint64_t value = 0xfeedfacedeadbeef;

    while (hickup_thread_running &&
           offset + sizeof(protocol_binary_request_no_extras) < buffersize) {
        union {
            protocol_binary_request_no_extras request;
            char bytes[65 * 1024];
        } command;
        uint8_t cmd = (uint8_t)(rand() & 0xff);
        size_t len;
        size_t keylen = (rand() % 250) + 1;

        switch (cmd) {
        case PROTOCOL_BINARY_CMD_ADD:
        case PROTOCOL_BINARY_CMD_ADDQ:
        case PROTOCOL_BINARY_CMD_REPLACE:
        case PROTOCOL_BINARY_CMD_REPLACEQ:
        case PROTOCOL_BINARY_CMD_SET:
        case PROTOCOL_BINARY_CMD_SETQ:
            len = storage_command(command.bytes, sizeof(command.bytes), cmd,
                                  key, keylen , &value, sizeof(value),
                                  0, 0);
            break;
        case PROTOCOL_BINARY_CMD_APPEND:
        case PROTOCOL_BINARY_CMD_APPENDQ:
        case PROTOCOL_BINARY_CMD_PREPEND:
        case PROTOCOL_BINARY_CMD_PREPENDQ:
            len = raw_command(command.bytes, sizeof(command.bytes), cmd,
                              key, keylen, &value, sizeof(value));
            break;
        case PROTOCOL_BINARY_CMD_FLUSH:
        case PROTOCOL_BINARY_CMD_FLUSHQ:
            len = raw_command(command.bytes, sizeof(command.bytes), cmd,
                              NULL, 0, NULL, 0);
            break;
        case PROTOCOL_BINARY_CMD_NOOP:
            len = raw_command(command.bytes, sizeof(command.bytes), cmd,
                              NULL, 0, NULL, 0);
            break;
        case PROTOCOL_BINARY_CMD_DELETE:
        case PROTOCOL_BINARY_CMD_DELETEQ:
            len = raw_command(command.bytes, sizeof(command.bytes), cmd,
                             key, keylen, NULL, 0);
            break;
        case PROTOCOL_BINARY_CMD_DECREMENT:
        case PROTOCOL_BINARY_CMD_DECREMENTQ:
        case PROTOCOL_BINARY_CMD_INCREMENT:
        case PROTOCOL_BINARY_CMD_INCREMENTQ:
            len = arithmetic_command(command.bytes, sizeof(command.bytes), cmd,
                                     key, keylen, 1, 0, 0);
            break;
        case PROTOCOL_BINARY_CMD_VERSION:
            len = raw_command(command.bytes, sizeof(command.bytes),
                             PROTOCOL_BINARY_CMD_VERSION,
                             NULL, 0, NULL, 0);
            break;
        case PROTOCOL_BINARY_CMD_GET:
        case PROTOCOL_BINARY_CMD_GETK:
        case PROTOCOL_BINARY_CMD_GETKQ:
        case PROTOCOL_BINARY_CMD_GETQ:
            len = raw_command(command.bytes, sizeof(command.bytes), cmd,
                             key, keylen, NULL, 0);
            break;

        case PROTOCOL_BINARY_CMD_TOUCH:
        case PROTOCOL_BINARY_CMD_GAT:
        case PROTOCOL_BINARY_CMD_GATQ:
        case PROTOCOL_BINARY_CMD_GATK:
        case PROTOCOL_BINARY_CMD_GATKQ:
            len = touch_command(command.bytes, sizeof(command.bytes), cmd,
                                key, keylen, 10);
            break;

        case PROTOCOL_BINARY_CMD_STAT:
            len = raw_command(command.bytes, sizeof(command.bytes),
                              PROTOCOL_BINARY_CMD_STAT,
                              NULL, 0, NULL, 0);
            break;

        case PROTOCOL_BINARY_CMD_SASL_LIST_MECHS:
        case PROTOCOL_BINARY_CMD_SASL_AUTH:
        case PROTOCOL_BINARY_CMD_SASL_STEP:
            /* Ignoring SASL */
        case PROTOCOL_BINARY_CMD_QUITQ:
        case PROTOCOL_BINARY_CMD_QUIT:
            /* I don't want to pass on the quit commands ;-) */
            cmd |= 0xf0;
            /* FALLTHROUGH */
        default:
            len = raw_command(command.bytes, sizeof(command.bytes),
                              cmd, NULL, 0, NULL, 0);
        }

        if ((len + offset) < buffersize) {
            memcpy(((char*)buffer) + offset, command.bytes, len);
            offset += len;
        } else {
            break;
        }
    }
    safe_send(buffer, offset, true);

    return TEST_PASS;
}