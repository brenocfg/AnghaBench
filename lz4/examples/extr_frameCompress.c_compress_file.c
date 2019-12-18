#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int member_0; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ compressResult_t ;
typedef  int /*<<< orphan*/  LZ4F_compressionContext_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t const IN_CHUNK_SIZE ; 
 int /*<<< orphan*/  LZ4F_VERSION ; 
 size_t LZ4F_compressBound (size_t const,int /*<<< orphan*/ *) ; 
 size_t LZ4F_createCompressionContext (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZ4F_freeCompressionContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZ4F_isError (size_t const) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ compress_file_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void* const,size_t const,void* const,size_t const) ; 
 int /*<<< orphan*/  free (void* const) ; 
 int /*<<< orphan*/  kPrefs ; 
 void* malloc (size_t const) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static compressResult_t
compress_file(FILE* f_in, FILE* f_out)
{
    assert(f_in != NULL);
    assert(f_out != NULL);

    /* ressource allocation */
    LZ4F_compressionContext_t ctx;
    size_t const ctxCreation = LZ4F_createCompressionContext(&ctx, LZ4F_VERSION);
    void* const src = malloc(IN_CHUNK_SIZE);
    size_t const outbufCapacity = LZ4F_compressBound(IN_CHUNK_SIZE, &kPrefs);   /* large enough for any input <= IN_CHUNK_SIZE */
    void* const outbuff = malloc(outbufCapacity);

    compressResult_t result = { 1, 0, 0 };  /* == error (default) */
    if (!LZ4F_isError(ctxCreation) && src && outbuff) {
        result = compress_file_internal(f_in, f_out,
                                        ctx,
                                        src, IN_CHUNK_SIZE,
                                        outbuff, outbufCapacity);
    } else {
        printf("error : ressource allocation failed \n");
    }

    LZ4F_freeCompressionContext(ctx);   /* supports free on NULL */
    free(src);
    free(outbuff);
    return result;
}