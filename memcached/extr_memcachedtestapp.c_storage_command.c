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
typedef  void* uint32_t ;
struct TYPE_9__ {void* expiration; void* flags; } ;
struct TYPE_7__ {int extlen; int opaque; int /*<<< orphan*/  bodylen; int /*<<< orphan*/  keylen; int /*<<< orphan*/  opcode; int /*<<< orphan*/  magic; } ;
struct TYPE_8__ {TYPE_1__ request; } ;
struct TYPE_10__ {TYPE_3__ body; TYPE_2__ header; } ;
struct TYPE_11__ {TYPE_4__ message; } ;
typedef  TYPE_5__ protocol_binary_request_set ;
typedef  int /*<<< orphan*/  protocol_binary_request_no_extras ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_REQ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  htonl (size_t) ; 
 int /*<<< orphan*/  htons (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static off_t storage_command(char*buf,
                             size_t bufsz,
                             uint8_t cmd,
                             const void* key,
                             size_t keylen,
                             const void* dta,
                             size_t dtalen,
                             uint32_t flags,
                             uint32_t exp) {
    /* all of the storage commands use the same command layout */
    protocol_binary_request_set *request = (void*)buf;
    assert(bufsz > sizeof(*request) + keylen + dtalen);

    memset(request, 0, sizeof(*request));
    request->message.header.request.magic = PROTOCOL_BINARY_REQ;
    request->message.header.request.opcode = cmd;
    request->message.header.request.keylen = htons(keylen);
    request->message.header.request.extlen = 8;
    request->message.header.request.bodylen = htonl(keylen + 8 + dtalen);
    request->message.header.request.opaque = 0xdeadbeef;
    request->message.body.flags = flags;
    request->message.body.expiration = exp;

    off_t key_offset = sizeof(protocol_binary_request_no_extras) + 8;

    memcpy(buf + key_offset, key, keylen);
    if (dta != NULL) {
        memcpy(buf + key_offset + keylen, dta, dtalen);
    }

    return key_offset + keylen + dtalen;
}