#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* callback ) (struct lwan_request*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;
struct lwan_response {int /*<<< orphan*/  buffer; TYPE_1__ stream; int /*<<< orphan*/  mime_type; } ;
struct lwan_request {int flags; struct lwan_response response; } ;
struct iovec {char* iov_base; size_t iov_len; } ;
typedef  int /*<<< orphan*/  headers ;
typedef  enum lwan_http_status { ____Placeholder_lwan_http_status } lwan_http_status ;

/* Variables and functions */
 int DEFAULT_HEADERS_SIZE ; 
 int HTTP_CLASS__CLIENT_ERROR ; 
 int HTTP_INTERNAL_ERROR ; 
 scalar_t__ LIKELY (int (*) (struct lwan_request*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  N_ELEMENTS (struct iovec*) ; 
 int RESPONSE_CHUNKED_ENCODING ; 
 int RESPONSE_SENT_HEADERS ; 
 int RESPONSE_STREAM ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  has_response_body (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_request (struct lwan_request*,int) ; 
 int /*<<< orphan*/  lwan_default_response (struct lwan_request*,int) ; 
 size_t lwan_prepare_response_header (struct lwan_request*,int,char*,int) ; 
 int /*<<< orphan*/  lwan_request_get_method (struct lwan_request*) ; 
 int /*<<< orphan*/  lwan_response_send_chunk (struct lwan_request*) ; 
 int /*<<< orphan*/  lwan_send (struct lwan_request*,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_status_debug (char*) ; 
 char* lwan_strbuf_get_buffer (int /*<<< orphan*/ ) ; 
 size_t lwan_strbuf_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_strbuf_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_writev (struct lwan_request*,struct iovec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t const) ; 
 int stub1 (struct lwan_request*,int /*<<< orphan*/ ) ; 

void lwan_response(struct lwan_request *request, enum lwan_http_status status)
{
    const struct lwan_response *response = &request->response;
    char headers[DEFAULT_HEADERS_SIZE];

    if (UNLIKELY(request->flags & RESPONSE_CHUNKED_ENCODING)) {
        /* Send last, 0-sized chunk */
        lwan_strbuf_reset(response->buffer);
        lwan_response_send_chunk(request);
        log_request(request, status);
        return;
    }

    if (UNLIKELY(request->flags & RESPONSE_SENT_HEADERS)) {
        lwan_status_debug("Headers already sent, ignoring call");
        return;
    }

    if (UNLIKELY(!response->mime_type)) {
        /* Requests without a MIME Type are errors from handlers that should
           just be handled by lwan_default_response().  */
        lwan_default_response(request, status);
        return;
    }

    log_request(request, status);

    if (request->flags & RESPONSE_STREAM) {
        if (LIKELY(response->stream.callback)) {
            status = response->stream.callback(request, response->stream.data);
        } else {
            status = HTTP_INTERNAL_ERROR;
        }

        if (status >= HTTP_CLASS__CLIENT_ERROR) {
            request->flags &= ~RESPONSE_STREAM;
            lwan_default_response(request, status);
        }

        return;
    }

    size_t header_len =
        lwan_prepare_response_header(request, status, headers, sizeof(headers));
    if (UNLIKELY(!header_len)) {
        lwan_default_response(request, HTTP_INTERNAL_ERROR);
        return;
    }

    if (!has_response_body(lwan_request_get_method(request), status)) {
        lwan_send(request, headers, header_len, 0);
        return;
    }

    char *resp_buf = lwan_strbuf_get_buffer(response->buffer);
    const size_t resp_len = lwan_strbuf_get_length(response->buffer);
    if (sizeof(headers) - header_len > resp_len) {
        /* writev() has to allocate, copy, and validate the response vector,
         * so use send() for responses small enough to fit the headers
         * buffer.  On Linux, this is ~10% faster.  */
        memcpy(headers + header_len, resp_buf, resp_len);
        lwan_send(request, headers, header_len + resp_len, 0);
    } else {
        struct iovec response_vec[] = {
            {.iov_base = headers, .iov_len = header_len},
            {.iov_base = resp_buf, .iov_len = resp_len},
        };

        lwan_writev(request, response_vec, N_ELEMENTS(response_vec));
    }
}