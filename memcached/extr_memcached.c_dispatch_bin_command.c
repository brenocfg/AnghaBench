#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_13__ {scalar_t__ extlen; scalar_t__ keylen; scalar_t__ bodylen; } ;
struct TYPE_14__ {TYPE_1__ request; } ;
struct TYPE_15__ {int noreply; int cmd; void* write_and_go; int /*<<< orphan*/  rbytes; int /*<<< orphan*/  rcurr; int /*<<< orphan*/  sfd; TYPE_2__ binary_header; } ;
typedef  TYPE_3__ conn ;
struct TYPE_16__ {scalar_t__ sasl; } ;

/* Variables and functions */
 scalar_t__ KEY_MAX_LENGTH ; 
 int /*<<< orphan*/  MEMCACHED_PROCESS_COMMAND_START (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_AUTH_ERROR ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_UNKNOWN_COMMAND ; 
 int /*<<< orphan*/ * VERSION ; 
 int /*<<< orphan*/  authenticated (TYPE_3__*) ; 
 int /*<<< orphan*/  bin_list_sasl_mechs (TYPE_3__*) ; 
 int /*<<< orphan*/  bin_read_flush_exptime ; 
 int /*<<< orphan*/  bin_read_key (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bin_reading_del_header ; 
 int /*<<< orphan*/  bin_reading_get_key ; 
 int /*<<< orphan*/  bin_reading_incr_header ; 
 int /*<<< orphan*/  bin_reading_sasl_auth ; 
 int /*<<< orphan*/  bin_reading_set_header ; 
 int /*<<< orphan*/  bin_reading_stat ; 
 int /*<<< orphan*/  bin_reading_touch_key ; 
 void* conn_closing ; 
 int /*<<< orphan*/  conn_set_state (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  handle_binary_protocol_error (TYPE_3__*) ; 
 TYPE_6__ settings ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_bin_error (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  write_bin_response (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispatch_bin_command(conn *c) {
    int protocol_error = 0;

    uint8_t extlen = c->binary_header.request.extlen;
    uint16_t keylen = c->binary_header.request.keylen;
    uint32_t bodylen = c->binary_header.request.bodylen;

    if (keylen > bodylen || keylen + extlen > bodylen) {
        write_bin_error(c, PROTOCOL_BINARY_RESPONSE_UNKNOWN_COMMAND, NULL, 0);
        c->write_and_go = conn_closing;
        return;
    }

    if (settings.sasl && !authenticated(c)) {
        write_bin_error(c, PROTOCOL_BINARY_RESPONSE_AUTH_ERROR, NULL, 0);
        c->write_and_go = conn_closing;
        return;
    }

    MEMCACHED_PROCESS_COMMAND_START(c->sfd, c->rcurr, c->rbytes);
    c->noreply = true;

    /* binprot supports 16bit keys, but internals are still 8bit */
    if (keylen > KEY_MAX_LENGTH) {
        handle_binary_protocol_error(c);
        return;
    }

    switch (c->cmd) {
    case PROTOCOL_BINARY_CMD_SETQ:
        c->cmd = PROTOCOL_BINARY_CMD_SET;
        break;
    case PROTOCOL_BINARY_CMD_ADDQ:
        c->cmd = PROTOCOL_BINARY_CMD_ADD;
        break;
    case PROTOCOL_BINARY_CMD_REPLACEQ:
        c->cmd = PROTOCOL_BINARY_CMD_REPLACE;
        break;
    case PROTOCOL_BINARY_CMD_DELETEQ:
        c->cmd = PROTOCOL_BINARY_CMD_DELETE;
        break;
    case PROTOCOL_BINARY_CMD_INCREMENTQ:
        c->cmd = PROTOCOL_BINARY_CMD_INCREMENT;
        break;
    case PROTOCOL_BINARY_CMD_DECREMENTQ:
        c->cmd = PROTOCOL_BINARY_CMD_DECREMENT;
        break;
    case PROTOCOL_BINARY_CMD_QUITQ:
        c->cmd = PROTOCOL_BINARY_CMD_QUIT;
        break;
    case PROTOCOL_BINARY_CMD_FLUSHQ:
        c->cmd = PROTOCOL_BINARY_CMD_FLUSH;
        break;
    case PROTOCOL_BINARY_CMD_APPENDQ:
        c->cmd = PROTOCOL_BINARY_CMD_APPEND;
        break;
    case PROTOCOL_BINARY_CMD_PREPENDQ:
        c->cmd = PROTOCOL_BINARY_CMD_PREPEND;
        break;
    case PROTOCOL_BINARY_CMD_GETQ:
        c->cmd = PROTOCOL_BINARY_CMD_GET;
        break;
    case PROTOCOL_BINARY_CMD_GETKQ:
        c->cmd = PROTOCOL_BINARY_CMD_GETK;
        break;
    case PROTOCOL_BINARY_CMD_GATQ:
        c->cmd = PROTOCOL_BINARY_CMD_GAT;
        break;
    case PROTOCOL_BINARY_CMD_GATKQ:
        c->cmd = PROTOCOL_BINARY_CMD_GATK;
        break;
    default:
        c->noreply = false;
    }

    switch (c->cmd) {
        case PROTOCOL_BINARY_CMD_VERSION:
            if (extlen == 0 && keylen == 0 && bodylen == 0) {
                write_bin_response(c, VERSION, 0, 0, strlen(VERSION));
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_FLUSH:
            if (keylen == 0 && bodylen == extlen && (extlen == 0 || extlen == 4)) {
                bin_read_key(c, bin_read_flush_exptime, extlen);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_NOOP:
            if (extlen == 0 && keylen == 0 && bodylen == 0) {
                write_bin_response(c, NULL, 0, 0, 0);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_SET: /* FALLTHROUGH */
        case PROTOCOL_BINARY_CMD_ADD: /* FALLTHROUGH */
        case PROTOCOL_BINARY_CMD_REPLACE:
            if (extlen == 8 && keylen != 0 && bodylen >= (keylen + 8)) {
                bin_read_key(c, bin_reading_set_header, 8);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_GETQ:  /* FALLTHROUGH */
        case PROTOCOL_BINARY_CMD_GET:   /* FALLTHROUGH */
        case PROTOCOL_BINARY_CMD_GETKQ: /* FALLTHROUGH */
        case PROTOCOL_BINARY_CMD_GETK:
            if (extlen == 0 && bodylen == keylen && keylen > 0) {
                bin_read_key(c, bin_reading_get_key, 0);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_DELETE:
            if (keylen > 0 && extlen == 0 && bodylen == keylen) {
                bin_read_key(c, bin_reading_del_header, extlen);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_INCREMENT:
        case PROTOCOL_BINARY_CMD_DECREMENT:
            if (keylen > 0 && extlen == 20 && bodylen == (keylen + extlen)) {
                bin_read_key(c, bin_reading_incr_header, 20);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_APPEND:
        case PROTOCOL_BINARY_CMD_PREPEND:
            if (keylen > 0 && extlen == 0) {
                bin_read_key(c, bin_reading_set_header, 0);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_STAT:
            if (extlen == 0) {
                bin_read_key(c, bin_reading_stat, 0);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_QUIT:
            if (keylen == 0 && extlen == 0 && bodylen == 0) {
                write_bin_response(c, NULL, 0, 0, 0);
                c->write_and_go = conn_closing;
                if (c->noreply) {
                    conn_set_state(c, conn_closing);
                }
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_SASL_LIST_MECHS:
            if (extlen == 0 && keylen == 0 && bodylen == 0) {
                bin_list_sasl_mechs(c);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_SASL_AUTH:
        case PROTOCOL_BINARY_CMD_SASL_STEP:
            if (extlen == 0 && keylen != 0) {
                bin_read_key(c, bin_reading_sasl_auth, 0);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_TOUCH:
        case PROTOCOL_BINARY_CMD_GAT:
        case PROTOCOL_BINARY_CMD_GATQ:
        case PROTOCOL_BINARY_CMD_GATK:
        case PROTOCOL_BINARY_CMD_GATKQ:
            if (extlen == 4 && keylen != 0) {
                bin_read_key(c, bin_reading_touch_key, 4);
            } else {
                protocol_error = 1;
            }
            break;
        default:
            write_bin_error(c, PROTOCOL_BINARY_RESPONSE_UNKNOWN_COMMAND, NULL,
                            bodylen);
    }

    if (protocol_error)
        handle_binary_protocol_error(c);
}