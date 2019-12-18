#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ outlen; scalar_t__ outpos; int /*<<< orphan*/ * out; scalar_t__ inpos; scalar_t__ inlen; int /*<<< orphan*/ * in; } ;
typedef  TYPE_1__ lzo_stream ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__,...) ; 
 scalar_t__ LZO_PAGE_SIZE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_INTERNAL_ERROR ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  do_lzo_decompress (TYPE_1__*) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

NTSTATUS lzo_decompress(uint8_t* inbuf, uint32_t inlen, uint8_t* outbuf, uint32_t outlen, uint32_t inpageoff) {
    NTSTATUS Status;
    uint32_t partlen, inoff, outoff;
    lzo_stream stream;

    inoff = 0;
    outoff = 0;

    do {
        partlen = *(uint32_t*)&inbuf[inoff];

        if (partlen + inoff > inlen) {
            ERR("overflow: %x + %x > %I64x\n", partlen, inoff, inlen);
            return STATUS_INTERNAL_ERROR;
        }

        inoff += sizeof(uint32_t);

        stream.in = &inbuf[inoff];
        stream.inlen = partlen;
        stream.inpos = 0;
        stream.out = &outbuf[outoff];
        stream.outlen = min(outlen, LZO_PAGE_SIZE);
        stream.outpos = 0;

        Status = do_lzo_decompress(&stream);
        if (!NT_SUCCESS(Status)) {
            ERR("do_lzo_decompress returned %08x\n", Status);
            return Status;
        }

        if (stream.outpos < stream.outlen)
            RtlZeroMemory(&stream.out[stream.outpos], stream.outlen - stream.outpos);

        inoff += partlen;
        outoff += stream.outlen;

        if (LZO_PAGE_SIZE - ((inpageoff + inoff) % LZO_PAGE_SIZE) < sizeof(uint32_t))
            inoff = ((((inpageoff + inoff) / LZO_PAGE_SIZE) + 1) * LZO_PAGE_SIZE) - inpageoff;

        outlen -= stream.outlen;
    } while (inoff < inlen && outlen > 0);

    return STATUS_SUCCESS;
}