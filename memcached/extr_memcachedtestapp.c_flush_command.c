#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  protocol_binary_request_no_extras ;
struct TYPE_8__ {int extlen; int opaque; void* bodylen; int /*<<< orphan*/  opcode; int /*<<< orphan*/  magic; } ;
struct TYPE_9__ {TYPE_2__ request; } ;
struct TYPE_7__ {void* expiration; } ;
struct TYPE_10__ {TYPE_3__ header; TYPE_1__ body; } ;
struct TYPE_11__ {TYPE_4__ message; } ;
typedef  TYPE_5__ protocol_binary_request_flush ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_REQ ; 
 int /*<<< orphan*/  assert (int) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static off_t flush_command(char* buf, size_t bufsz, uint8_t cmd, uint32_t exptime, bool use_extra) {
    protocol_binary_request_flush *request = (void*)buf;
    assert(bufsz > sizeof(*request));

    memset(request, 0, sizeof(*request));
    request->message.header.request.magic = PROTOCOL_BINARY_REQ;
    request->message.header.request.opcode = cmd;

    off_t size = sizeof(protocol_binary_request_no_extras);
    if (use_extra) {
        request->message.header.request.extlen = 4;
        request->message.body.expiration = htonl(exptime);
        request->message.header.request.bodylen = htonl(4);
        size += 4;
    }

    request->message.header.request.opaque = 0xdeadbeef;

    return size;
}