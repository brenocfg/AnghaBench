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
struct TYPE_6__ {size_t extlen; int opaque; int /*<<< orphan*/  bodylen; int /*<<< orphan*/  keylen; int /*<<< orphan*/  opcode; int /*<<< orphan*/  magic; } ;
struct TYPE_7__ {TYPE_1__ request; } ;
struct TYPE_8__ {TYPE_2__ header; } ;
struct TYPE_9__ {TYPE_3__ message; } ;
typedef  TYPE_4__ protocol_binary_request_no_extras ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_REQ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  htonl (size_t) ; 
 int /*<<< orphan*/  htons (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static off_t ext_command(char* buf,
                         size_t bufsz,
                         uint8_t cmd,
                         const void* ext,
                         size_t extlen,
                         const void* key,
                         size_t keylen,
                         const void* dta,
                         size_t dtalen) {
    protocol_binary_request_no_extras *request = (void*)buf;
    assert(bufsz > sizeof(*request) + extlen + keylen + dtalen);

    memset(request, 0, sizeof(*request));
    request->message.header.request.magic = PROTOCOL_BINARY_REQ;
    request->message.header.request.opcode = cmd;
    request->message.header.request.extlen = extlen;
    request->message.header.request.keylen = htons(keylen);
    request->message.header.request.bodylen = htonl(extlen + keylen + dtalen);
    request->message.header.request.opaque = 0xdeadbeef;

    off_t ext_offset = sizeof(protocol_binary_request_no_extras);
    off_t key_offset = ext_offset + extlen;
    off_t dta_offset = key_offset + keylen;

    if (ext != NULL) {
        memcpy(buf + ext_offset, ext, extlen);
    }
    if (key != NULL) {
        memcpy(buf + key_offset, key, keylen);
    }
    if (dta != NULL) {
        memcpy(buf + dta_offset, dta, dtalen);
    }

    return sizeof(*request) + extlen + keylen + dtalen;
}