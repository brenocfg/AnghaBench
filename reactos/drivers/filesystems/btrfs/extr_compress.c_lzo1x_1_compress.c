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
typedef  int uint32_t ;
struct TYPE_3__ {int inlen; int outlen; int inpos; int /*<<< orphan*/ * out; int /*<<< orphan*/  wrkmem; int /*<<< orphan*/ * in; } ;
typedef  TYPE_1__ lzo_stream ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  LZO_BYTE (int) ; 
 int M4_MARKER ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ lzo_do_compress (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static NTSTATUS lzo1x_1_compress(lzo_stream* stream) {
    uint8_t *op = stream->out;
    NTSTATUS Status = STATUS_SUCCESS;

    if (stream->inlen <= 0)
        stream->outlen = 0;
    else if (stream->inlen <= 9 + 4) {
        *op++ = LZO_BYTE(17 + stream->inlen);

        stream->inpos = 0;
        do {
            *op++ = stream->in[stream->inpos];
            stream->inpos++;
        } while (stream->inlen < stream->inpos);
        stream->outlen = (uint32_t)(op - stream->out);
    } else
        Status = lzo_do_compress(stream->in, stream->inlen, stream->out, &stream->outlen, stream->wrkmem);

    if (Status == STATUS_SUCCESS) {
        op = stream->out + stream->outlen;
        *op++ = M4_MARKER | 1;
        *op++ = 0;
        *op++ = 0;
        stream->outlen += 3;
    }

    return Status;
}