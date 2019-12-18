#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* uint16_t ;
struct TYPE_14__ {int /*<<< orphan*/  cas; int /*<<< orphan*/  opaque; int /*<<< orphan*/  bodylen; void* status; void* datatype; void* extlen; void* keylen; int /*<<< orphan*/  opcode; void* magic; } ;
struct TYPE_15__ {int* bytes; TYPE_3__ response; } ;
typedef  TYPE_4__ protocol_binary_response_header ;
struct TYPE_12__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_13__ {TYPE_1__ request; } ;
struct TYPE_16__ {int sfd; scalar_t__ wbuf; int /*<<< orphan*/  cas; int /*<<< orphan*/  opaque; TYPE_2__ binary_header; scalar_t__ iovused; scalar_t__ msgused; scalar_t__ msgcurr; } ;
typedef  TYPE_5__ conn ;
struct TYPE_17__ {int verbose; } ;

/* Variables and functions */
 scalar_t__ PROTOCOL_BINARY_RAW_BYTES ; 
 scalar_t__ PROTOCOL_BINARY_RES ; 
 int /*<<< orphan*/  add_iov (TYPE_5__*,scalar_t__,int) ; 
 scalar_t__ add_msghdr (TYPE_5__*) ; 
 int /*<<< orphan*/  assert (TYPE_5__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonll (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (void*) ; 
 int /*<<< orphan*/  out_of_memory (TYPE_5__*,char*) ; 
 TYPE_6__ settings ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void add_bin_header(conn *c, uint16_t err, uint8_t hdr_len, uint16_t key_len, uint32_t body_len) {
    protocol_binary_response_header* header;

    assert(c);

    c->msgcurr = 0;
    c->msgused = 0;
    c->iovused = 0;
    if (add_msghdr(c) != 0) {
        /* This should never run out of memory because iov and msg lists
         * have minimum sizes big enough to hold an error response.
         */
        out_of_memory(c, "SERVER_ERROR out of memory adding binary header");
        return;
    }

    header = (protocol_binary_response_header *)c->wbuf;

    header->response.magic = (uint8_t)PROTOCOL_BINARY_RES;
    header->response.opcode = c->binary_header.request.opcode;
    header->response.keylen = (uint16_t)htons(key_len);

    header->response.extlen = (uint8_t)hdr_len;
    header->response.datatype = (uint8_t)PROTOCOL_BINARY_RAW_BYTES;
    header->response.status = (uint16_t)htons(err);

    header->response.bodylen = htonl(body_len);
    header->response.opaque = c->opaque;
    header->response.cas = htonll(c->cas);

    if (settings.verbose > 1) {
        int ii;
        fprintf(stderr, ">%d Writing bin response:", c->sfd);
        for (ii = 0; ii < sizeof(header->bytes); ++ii) {
            if (ii % 4 == 0) {
                fprintf(stderr, "\n>%d  ", c->sfd);
            }
            fprintf(stderr, " 0x%02x", header->bytes[ii]);
        }
        fprintf(stderr, "\n");
    }

    add_iov(c, c->wbuf, sizeof(header->response));
}