#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint32_t ;
struct TYPE_5__ {scalar_t__ pos; void* size; int /*<<< orphan*/ * dst; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;
struct TYPE_6__ {scalar_t__ pos; void* size; int /*<<< orphan*/ * src; } ;
typedef  TYPE_2__ ZSTD_inBuffer ;
typedef  int /*<<< orphan*/  ZSTD_DStream ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  STATUS_INTERNAL_ERROR ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/ * ZSTD_createDStream_advanced (int /*<<< orphan*/ ) ; 
 size_t ZSTD_decompressStream (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ZSTD_freeDStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_getErrorName (size_t) ; 
 size_t ZSTD_initDStream (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int /*<<< orphan*/  zstd_mem ; 

NTSTATUS zstd_decompress(uint8_t* inbuf, uint32_t inlen, uint8_t* outbuf, uint32_t outlen) {
    NTSTATUS Status;
    ZSTD_DStream* stream;
    size_t init_res, read;
    ZSTD_inBuffer input;
    ZSTD_outBuffer output;

    stream = ZSTD_createDStream_advanced(zstd_mem);

    if (!stream) {
        ERR("ZSTD_createDStream failed.\n");
        return STATUS_INTERNAL_ERROR;
    }

    init_res = ZSTD_initDStream(stream);

    if (ZSTD_isError(init_res)) {
        ERR("ZSTD_initDStream failed: %s\n", ZSTD_getErrorName(init_res));
        Status = STATUS_INTERNAL_ERROR;
        goto end;
    }

    input.src = inbuf;
    input.size = inlen;
    input.pos = 0;

    output.dst = outbuf;
    output.size = outlen;
    output.pos = 0;

    read = ZSTD_decompressStream(stream, &output, &input);

    if (ZSTD_isError(read)) {
        ERR("ZSTD_decompressStream failed: %s\n", ZSTD_getErrorName(read));
        Status = STATUS_INTERNAL_ERROR;
        goto end;
    }

    Status = STATUS_SUCCESS;

end:
    ZSTD_freeDStream(stream);

    return Status;
}