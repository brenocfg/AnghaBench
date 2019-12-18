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
struct TYPE_4__ {int zoutput; size_t sent; scalar_t__ rlen; TYPE_1__* data; } ;
struct web_client {scalar_t__ mode; int /*<<< orphan*/  id; TYPE_2__ response; int /*<<< orphan*/  stats_sent_bytes; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_WEB_CLIENT ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  WEB_CLIENT_IS_DEAD (struct web_client*) ; 
 scalar_t__ WEB_CLIENT_MODE_FILECOPY ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  web_client_disable_wait_send (struct web_client*) ; 
 int /*<<< orphan*/  web_client_has_keepalive (struct web_client*) ; 
 scalar_t__ web_client_has_wait_receive (struct web_client*) ; 
 int /*<<< orphan*/  web_client_request_done (struct web_client*) ; 
 scalar_t__ web_client_send_data (struct web_client*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ web_client_send_deflate (struct web_client*) ; 

ssize_t web_client_send(struct web_client *w) {
#ifdef NETDATA_WITH_ZLIB
    if(likely(w->response.zoutput)) return web_client_send_deflate(w);
#endif // NETDATA_WITH_ZLIB

    ssize_t bytes;

    if(unlikely(w->response.data->len - w->response.sent == 0)) {
        // there is nothing to send

        debug(D_WEB_CLIENT, "%llu: Out of output data.", w->id);

        // there can be two cases for this
        // A. we have done everything
        // B. we temporarily have nothing to send, waiting for the buffer to be filled by ifd

        if(w->mode == WEB_CLIENT_MODE_FILECOPY && web_client_has_wait_receive(w) && w->response.rlen && w->response.rlen > w->response.data->len) {
            // we have to wait, more data will come
            debug(D_WEB_CLIENT, "%llu: Waiting for more data to become available.", w->id);
            web_client_disable_wait_send(w);
            return 0;
        }

        if(unlikely(!web_client_has_keepalive(w))) {
            debug(D_WEB_CLIENT, "%llu: Closing (keep-alive is not enabled). %zu bytes sent.", w->id, w->response.sent);
            WEB_CLIENT_IS_DEAD(w);
            return 0;
        }

        web_client_request_done(w);
        debug(D_WEB_CLIENT, "%llu: Done sending all data on socket. Waiting for next request on the same socket.", w->id);
        return 0;
    }

    bytes = web_client_send_data(w,&w->response.data->buffer[w->response.sent], w->response.data->len - w->response.sent, MSG_DONTWAIT);
    if(likely(bytes > 0)) {
        w->stats_sent_bytes += bytes;
        w->response.sent += bytes;
        debug(D_WEB_CLIENT, "%llu: Sent %zd bytes.", w->id, bytes);
    }
    else if(likely(bytes == 0)) {
        debug(D_WEB_CLIENT, "%llu: Did not send any bytes to the client.", w->id);
        WEB_CLIENT_IS_DEAD(w);
    }
    else {
        debug(D_WEB_CLIENT, "%llu: Failed to send data to client.", w->id);
        WEB_CLIENT_IS_DEAD(w);
    }

    return(bytes);
}