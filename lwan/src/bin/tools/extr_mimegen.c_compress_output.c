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
typedef  int /*<<< orphan*/  uLong ;
struct output {scalar_t__ used; scalar_t__ ptr; } ;
typedef  int /*<<< orphan*/  ZopfliOptions ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_MAX_QUALITY ; 
 int /*<<< orphan*/  BROTLI_MAX_WINDOW_BITS ; 
 int /*<<< orphan*/  BROTLI_MODE_TEXT ; 
 scalar_t__ BROTLI_TRUE ; 
 scalar_t__ BrotliEncoderCompress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned char const*,size_t*,unsigned char*) ; 
 size_t BrotliEncoderMaxCompressedSize (scalar_t__) ; 
 int /*<<< orphan*/  ZOPFLI_FORMAT_ZLIB ; 
 size_t ZSTD_compress (char*,size_t,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t ZSTD_compressBound (scalar_t__) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int /*<<< orphan*/  ZSTD_maxCLevel () ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  ZopfliCompress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char const*,scalar_t__,unsigned char**,size_t*) ; 
 int /*<<< orphan*/  ZopfliInitOptions (int /*<<< orphan*/ *) ; 
 scalar_t__ compress2 (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/  const*,scalar_t__,int) ; 
 size_t compressBound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static char *compress_output(const struct output *output, size_t *outlen)
{
    char *compressed;

#if defined(HAVE_ZSTD)
    *outlen = ZSTD_compressBound(output->used);

    compressed = malloc(*outlen);
    if (!compressed) {
        fprintf(stderr, "Could not allocate memory for compressed data\n");
        exit(1);
    }

    *outlen = ZSTD_compress(compressed, *outlen, output->ptr, output->used,
                            ZSTD_maxCLevel());
    if (ZSTD_isError(*outlen)) {
        fprintf(stderr, "Could not compress mime type table with Brotli\n");
        exit(1);
    }
#elif defined(HAVE_BROTLI)
    *outlen = BrotliEncoderMaxCompressedSize(output->used);

    compressed = malloc(*outlen);
    if (!compressed) {
        fprintf(stderr, "Could not allocate memory for compressed data\n");
        exit(1);
    }

    if (BrotliEncoderCompress(BROTLI_MAX_QUALITY, BROTLI_MAX_WINDOW_BITS,
                              BROTLI_MODE_TEXT, output->used,
                              (const unsigned char *)output->ptr, outlen,
                              (unsigned char *)compressed) != BROTLI_TRUE) {
        fprintf(stderr, "Could not compress mime type table with Brotli\n");
        exit(1);
    }
#elif defined(HAVE_ZOPFLI)
    ZopfliOptions opts;

    *outlen = 0;

    ZopfliInitOptions(&opts);
    ZopfliCompress(&opts, ZOPFLI_FORMAT_ZLIB,
                   (const unsigned char *)output->ptr, output->used,
                   (unsigned char **)&compressed, outlen);
#else
    *outlen = compressBound((uLong)output->used);
    compressed = malloc(*outlen);
    if (!compressed) {
        fprintf(stderr, "Could not allocate memory for compressed data\n");
        exit(1);
    }
    if (compress2((Bytef *)compressed, outlen, (const Bytef *)output->ptr,
                  output->used, 9) != Z_OK) {
        fprintf(stderr, "Could not compress data with zlib\n");
        exit(1);
    }
#endif
    if (!*outlen) {
        free(compressed);
        return NULL;
    }

    return compressed;
}