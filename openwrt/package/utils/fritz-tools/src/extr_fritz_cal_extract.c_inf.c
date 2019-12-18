#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ avail_in; unsigned char* next_in; scalar_t__ avail_out; unsigned char* next_out; void* opaque; void* zfree; void* zalloc; } ;
typedef  TYPE_1__ z_stream ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CHUNK ; 
#define  Z_DATA_ERROR 130 
 int Z_ERRNO ; 
#define  Z_MEM_ERROR 129 
#define  Z_NEED_DICT 128 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 void* Z_NULL ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int Z_STREAM_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int fwrite (unsigned char*,size_t,int,int /*<<< orphan*/ *) ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inflateEnd (TYPE_1__*) ; 
 int inflateInit (TYPE_1__*) ; 
 size_t special_min (size_t,int) ; 

__attribute__((used)) static int inf(FILE *source, FILE *dest, size_t limit, size_t skip)
{
    int ret;
    size_t have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

    /* decompress until deflate stream ends or end of file */
    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;

        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }
            have = special_min(limit, CHUNK - strm.avail_out) - skip;
            if (fwrite(&out[skip], have, 1, dest) != 1 || ferror(dest)) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
	    skip = 0;
	    limit -= have;
        } while (strm.avail_out == 0 && limit > 0);

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END && limit > 0);

    /* clean up and return */
    (void)inflateEnd(&strm);
    return (limit == 0 ? Z_OK : (ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR));
}