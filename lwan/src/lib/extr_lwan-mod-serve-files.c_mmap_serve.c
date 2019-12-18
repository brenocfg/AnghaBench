#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ value; scalar_t__ len; } ;
struct TYPE_7__ {size_t len; void* value; } ;
struct TYPE_6__ {size_t len; void* value; } ;
struct TYPE_5__ {size_t len; void* value; } ;
struct mmap_cache_data {TYPE_4__ uncompressed; TYPE_3__ deflated; TYPE_2__ brotli; TYPE_1__ zstd; } ;
struct lwan_request {int flags; } ;
struct lwan_key_value {int dummy; } ;
struct file_cache_entry {struct mmap_cache_data mmap_cache_data; } ;
typedef  scalar_t__ off_t ;
typedef  enum lwan_http_status { ____Placeholder_lwan_http_status } lwan_http_status ;

/* Variables and functions */
#define  HTTP_OK 129 
#define  HTTP_PARTIAL_CONTENT 128 
 int REQUEST_ACCEPT_BROTLI ; 
 int REQUEST_ACCEPT_DEFLATE ; 
 int REQUEST_ACCEPT_ZSTD ; 
 struct lwan_key_value br_compression_hdr ; 
 int compute_range (struct lwan_request*,scalar_t__*,scalar_t__*,scalar_t__) ; 
 struct lwan_key_value deflate_compression_hdr ; 
 int serve_buffer (struct lwan_request*,struct file_cache_entry*,struct lwan_key_value const*,void*,size_t,int) ; 
 struct lwan_key_value zstd_compression_hdr ; 

__attribute__((used)) static enum lwan_http_status mmap_serve(struct lwan_request *request,
                                        void *data)
{
    const struct lwan_key_value *compressed;
    struct file_cache_entry *fce = data;
    struct mmap_cache_data *md = &fce->mmap_cache_data;
    void *contents;
    size_t size;
    enum lwan_http_status status;

#if defined(HAVE_ZSTD)
    if (md->zstd.len && (request->flags & REQUEST_ACCEPT_ZSTD)) {
        contents = md->zstd.value;
        size = md->zstd.len;
        compressed = &zstd_compression_hdr;

        status = HTTP_OK;
    } else
#elif defined(HAVE_BROTLI)
    if (md->brotli.len && (request->flags & REQUEST_ACCEPT_BROTLI)) {
        contents = md->brotli.value;
        size = md->brotli.len;
        compressed = &br_compression_hdr;

        status = HTTP_OK;
    } else
#endif
    if (md->deflated.len && (request->flags & REQUEST_ACCEPT_DEFLATE)) {
        contents = md->deflated.value;
        size = md->deflated.len;
        compressed = &deflate_compression_hdr;

        status = HTTP_OK;
    } else {
        off_t from, to;

        status =
            compute_range(request, &from, &to, (off_t)md->uncompressed.len);
        switch (status) {
        case HTTP_PARTIAL_CONTENT:
        case HTTP_OK:
            contents = (char *)md->uncompressed.value + from;
            size = (size_t)(to - from);
            compressed = NULL;
            break;

        default:
            return status;
        }
    }

    return serve_buffer(request, fce, compressed, contents, size, status);
}