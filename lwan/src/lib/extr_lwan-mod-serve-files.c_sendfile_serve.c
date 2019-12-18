#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fd; scalar_t__ size; } ;
struct TYPE_3__ {size_t size; int fd; } ;
struct sendfile_cache_data {TYPE_2__ uncompressed; TYPE_1__ compressed; } ;
struct lwan_request {int flags; } ;
struct lwan_key_value {int dummy; } ;
struct file_cache_entry {struct sendfile_cache_data sendfile_cache_data; } ;
typedef  scalar_t__ off_t ;
typedef  enum lwan_http_status { ____Placeholder_lwan_http_status } lwan_http_status ;

/* Variables and functions */
 int DEFAULT_HEADERS_SIZE ; 
#define  EACCES 130 
#define  EMFILE 129 
#define  ENFILE 128 
 int HTTP_FORBIDDEN ; 
 int HTTP_INTERNAL_ERROR ; 
 int HTTP_OK ; 
 int HTTP_RANGE_UNSATISFIABLE ; 
 int HTTP_UNAVAILABLE ; 
 int REQUEST_ACCEPT_GZIP ; 
 scalar_t__ REQUEST_METHOD_HEAD ; 
 scalar_t__ UNLIKELY (int) ; 
 int compute_range (struct lwan_request*,scalar_t__*,scalar_t__*,scalar_t__) ; 
 struct lwan_key_value gzip_compression_hdr ; 
 scalar_t__ lwan_request_get_method (struct lwan_request*) ; 
 int /*<<< orphan*/  lwan_send (struct lwan_request*,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_sendfile (struct lwan_request*,int,scalar_t__,size_t,char*,size_t) ; 
 size_t prepare_headers (struct lwan_request*,int,struct file_cache_entry*,size_t,struct lwan_key_value const*,char*) ; 

__attribute__((used)) static enum lwan_http_status sendfile_serve(struct lwan_request *request,
                                            void *data)
{
    const struct lwan_key_value *compression_hdr;
    struct file_cache_entry *fce = data;
    struct sendfile_cache_data *sd = &fce->sendfile_cache_data;
    char headers[DEFAULT_HEADERS_SIZE];
    size_t header_len;
    enum lwan_http_status return_status;
    off_t from, to;
    size_t size;
    int fd;

    if (sd->compressed.size && (request->flags & REQUEST_ACCEPT_GZIP)) {
        from = 0;
        to = (off_t)sd->compressed.size;

        compression_hdr = &gzip_compression_hdr;
        fd = sd->compressed.fd;
        size = sd->compressed.size;

        return_status = HTTP_OK;
    } else {
        return_status =
            compute_range(request, &from, &to, (off_t)sd->uncompressed.size);
        if (UNLIKELY(return_status == HTTP_RANGE_UNSATISFIABLE))
            return HTTP_RANGE_UNSATISFIABLE;

        compression_hdr = NULL;
        fd = sd->uncompressed.fd;
        size = (size_t)(to - from);
    }
    if (UNLIKELY(fd < 0)) {
        switch (-fd) {
        case EACCES:
            return HTTP_FORBIDDEN;
        case EMFILE:
        case ENFILE:
            return HTTP_UNAVAILABLE;
        default:
            return HTTP_INTERNAL_ERROR;
        }
    }

    header_len = prepare_headers(request, return_status, fce, size,
                                 compression_hdr, headers);
    if (UNLIKELY(!header_len))
        return HTTP_INTERNAL_ERROR;

    if (lwan_request_get_method(request) == REQUEST_METHOD_HEAD) {
        lwan_send(request, headers, header_len, 0);
    } else {
        lwan_sendfile(request, fd, from, (size_t)to, headers, header_len);
    }

    return return_status;
}