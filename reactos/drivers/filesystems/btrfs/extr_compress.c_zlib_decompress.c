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
struct TYPE_5__ {scalar_t__ avail_out; int /*<<< orphan*/ * next_out; void* avail_in; int /*<<< orphan*/ * next_in; scalar_t__ opaque; int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; } ;
typedef  TYPE_1__ z_stream ;
typedef  scalar_t__ voidpf ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  STATUS_INTERNAL_ERROR ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int inflateEnd (TYPE_1__*) ; 
 int inflateInit (TYPE_1__*) ; 
 int /*<<< orphan*/  zlib_alloc ; 
 int /*<<< orphan*/  zlib_free ; 

NTSTATUS zlib_decompress(uint8_t* inbuf, uint32_t inlen, uint8_t* outbuf, uint32_t outlen) {
    z_stream c_stream;
    int ret;

    c_stream.zalloc = zlib_alloc;
    c_stream.zfree = zlib_free;
    c_stream.opaque = (voidpf)0;

    ret = inflateInit(&c_stream);

    if (ret != Z_OK) {
        ERR("inflateInit returned %08x\n", ret);
        return STATUS_INTERNAL_ERROR;
    }

    c_stream.next_in = inbuf;
    c_stream.avail_in = inlen;

    c_stream.next_out = outbuf;
    c_stream.avail_out = outlen;

    do {
        ret = inflate(&c_stream, Z_NO_FLUSH);

        if (ret != Z_OK && ret != Z_STREAM_END) {
            ERR("inflate returned %08x\n", ret);
            inflateEnd(&c_stream);
            return STATUS_INTERNAL_ERROR;
        }

        if (c_stream.avail_out == 0)
            break;
    } while (ret != Z_STREAM_END);

    ret = inflateEnd(&c_stream);

    if (ret != Z_OK) {
        ERR("inflateEnd returned %08x\n", ret);
        return STATUS_INTERNAL_ERROR;
    }

    // FIXME - if we're short, should we zero the end of outbuf so we don't leak information into userspace?

    return STATUS_SUCCESS;
}