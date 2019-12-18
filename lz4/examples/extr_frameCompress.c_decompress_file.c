#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  LZ4F_dctx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  IN_CHUNK_SIZE ; 
 int /*<<< orphan*/  LZ4F_VERSION ; 
 size_t LZ4F_createDecompressionContext (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZ4F_freeDecompressionContext (int /*<<< orphan*/ *) ; 
 char* LZ4F_getErrorName (size_t const) ; 
 scalar_t__ LZ4F_isError (size_t const) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int decompress_file_allocDst (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void* const) ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int decompress_file(FILE* f_in, FILE* f_out)
{
    assert(f_in != NULL); assert(f_out != NULL);

    /* Ressource allocation */
    void* const src = malloc(IN_CHUNK_SIZE);
    if (!src) { perror("decompress_file(src)"); return 1; }

    LZ4F_dctx* dctx;
    {   size_t const dctxStatus = LZ4F_createDecompressionContext(&dctx, LZ4F_VERSION);
        if (LZ4F_isError(dctxStatus)) {
            printf("LZ4F_dctx creation error: %s\n", LZ4F_getErrorName(dctxStatus));
    }   }

    int const result = !dctx ? 1 /* error */ :
                       decompress_file_allocDst(f_in, f_out, dctx, src, IN_CHUNK_SIZE);

    free(src);
    LZ4F_freeDecompressionContext(dctx);   /* note : free works on NULL */
    return result;
}