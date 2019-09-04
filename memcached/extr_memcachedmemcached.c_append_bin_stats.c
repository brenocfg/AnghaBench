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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_6__ {int keylen; int /*<<< orphan*/  opaque; int /*<<< orphan*/  bodylen; int /*<<< orphan*/  datatype; int /*<<< orphan*/  opcode; int /*<<< orphan*/  magic; } ;
struct TYPE_8__ {char const* bytes; TYPE_1__ response; } ;
typedef  TYPE_3__ protocol_binary_response_header ;
struct TYPE_7__ {char* buffer; int offset; } ;
struct TYPE_9__ {TYPE_2__ stats; int /*<<< orphan*/  opaque; } ;
typedef  TYPE_4__ conn ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_CMD_STAT ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_RAW_BYTES ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_RES ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int const) ; 

__attribute__((used)) static void append_bin_stats(const char *key, const uint16_t klen,
                             const char *val, const uint32_t vlen,
                             conn *c) {
    char *buf = c->stats.buffer + c->stats.offset;
    uint32_t bodylen = klen + vlen;
    protocol_binary_response_header header = {
        .response.magic = (uint8_t)PROTOCOL_BINARY_RES,
        .response.opcode = PROTOCOL_BINARY_CMD_STAT,
        .response.keylen = (uint16_t)htons(klen),
        .response.datatype = (uint8_t)PROTOCOL_BINARY_RAW_BYTES,
        .response.bodylen = htonl(bodylen),
        .response.opaque = c->opaque
    };

    memcpy(buf, header.bytes, sizeof(header.response));
    buf += sizeof(header.response);

    if (klen > 0) {
        memcpy(buf, key, klen);
        buf += klen;

        if (vlen > 0) {
            memcpy(buf, val, vlen);
        }
    }

    c->stats.offset += sizeof(header.response) + bodylen;
}