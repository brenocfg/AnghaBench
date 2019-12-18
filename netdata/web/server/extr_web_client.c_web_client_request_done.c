#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ total_out; scalar_t__ total_in; scalar_t__ avail_out; scalar_t__ avail_in; } ;
struct TYPE_4__ {size_t rlen; char zoutput; scalar_t__ zinitialized; TYPE_2__ zstream; scalar_t__ zhave; scalar_t__ zsent; scalar_t__ code; scalar_t__ sent; TYPE_3__* data; TYPE_3__* header; TYPE_3__* header_output; } ;
struct timeval {int dummy; } ;
struct web_client {char* last_url; int mode; int ifd; int ofd; char* cookie1; char* cookie2; char* origin; char* decoded_url; TYPE_1__ response; int /*<<< orphan*/  id; scalar_t__ header_parse_last_size; scalar_t__ header_parse_tries; scalar_t__ tcp_cork; int /*<<< orphan*/ * auth_bearer_token; int /*<<< orphan*/ * user_agent; struct timeval tv_in; struct timeval tv_ready; int /*<<< orphan*/  client_port; int /*<<< orphan*/  client_ip; int /*<<< orphan*/  stats_sent_bytes; int /*<<< orphan*/  stats_received_bytes; } ;
struct TYPE_6__ {size_t len; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_DEFLATE ; 
 int /*<<< orphan*/  D_WEB_CLIENT ; 
#define  WEB_CLIENT_MODE_FILECOPY 131 
#define  WEB_CLIENT_MODE_NORMAL 130 
#define  WEB_CLIENT_MODE_OPTIONS 129 
#define  WEB_CLIENT_MODE_STREAM 128 
 scalar_t__ WEB_SERVER_MODE_STATIC_THREADED ; 
 int /*<<< orphan*/  buffer_reset (TYPE_3__*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  deflateEnd (TYPE_2__*) ; 
 double dt_usec (struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  finished_web_request_statistics (double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  freez (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gettid () ; 
 scalar_t__ likely (char) ; 
 int /*<<< orphan*/  log_access (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t,size_t,size_t,double,double,double,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  now_realtime_timeval (struct timeval*) ; 
 int /*<<< orphan*/  strip_control_characters (char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  web_client_disable_donottrack (struct web_client*) ; 
 int /*<<< orphan*/  web_client_disable_keepalive (struct web_client*) ; 
 int /*<<< orphan*/  web_client_disable_tracking_required (struct web_client*) ; 
 int /*<<< orphan*/  web_client_disable_wait_send (struct web_client*) ; 
 int /*<<< orphan*/  web_client_enable_wait_receive (struct web_client*) ; 
 int /*<<< orphan*/  web_client_uncrock_socket (struct web_client*) ; 
 scalar_t__ web_server_mode ; 

void web_client_request_done(struct web_client *w) {
    web_client_uncrock_socket(w);

    debug(D_WEB_CLIENT, "%llu: Resetting client.", w->id);

    if(likely(w->last_url[0])) {
        struct timeval tv;
        now_realtime_timeval(&tv);

        size_t size = (w->mode == WEB_CLIENT_MODE_FILECOPY)?w->response.rlen:w->response.data->len;
        size_t sent = size;
#ifdef NETDATA_WITH_ZLIB
        if(likely(w->response.zoutput)) sent = (size_t)w->response.zstream.total_out;
#endif

        // --------------------------------------------------------------------
        // global statistics

        finished_web_request_statistics(dt_usec(&tv, &w->tv_in),
                                        w->stats_received_bytes,
                                        w->stats_sent_bytes,
                                        size,
                                        sent);

        w->stats_received_bytes = 0;
        w->stats_sent_bytes = 0;


        // --------------------------------------------------------------------

        const char *mode;
        switch(w->mode) {
            case WEB_CLIENT_MODE_FILECOPY:
                mode = "FILECOPY";
                break;

            case WEB_CLIENT_MODE_OPTIONS:
                mode = "OPTIONS";
                break;

            case WEB_CLIENT_MODE_STREAM:
                mode = "STREAM";
                break;

            case WEB_CLIENT_MODE_NORMAL:
                mode = "DATA";
                break;

            default:
                mode = "UNKNOWN";
                break;
        }

        // access log
        log_access("%llu: %d '[%s]:%s' '%s' (sent/all = %zu/%zu bytes %0.0f%%, prep/sent/total = %0.2f/%0.2f/%0.2f ms) %d '%s'",
                   w->id
                   , gettid()
                   , w->client_ip
                   , w->client_port
                   , mode
                   , sent
                   , size
                   , -((size > 0) ? ((size - sent) / (double) size * 100.0) : 0.0)
                   , dt_usec(&w->tv_ready, &w->tv_in) / 1000.0
                   , dt_usec(&tv, &w->tv_ready) / 1000.0
                   , dt_usec(&tv, &w->tv_in) / 1000.0
                   , w->response.code
                   , strip_control_characters(w->last_url)
        );
    }

    if(unlikely(w->mode == WEB_CLIENT_MODE_FILECOPY)) {
        if(w->ifd != w->ofd) {
            debug(D_WEB_CLIENT, "%llu: Closing filecopy input file descriptor %d.", w->id, w->ifd);

            if(web_server_mode != WEB_SERVER_MODE_STATIC_THREADED) {
                if (w->ifd != -1){
                    close(w->ifd);
                }
            }

            w->ifd = w->ofd;
        }
    }

    w->last_url[0] = '\0';
    w->cookie1[0] = '\0';
    w->cookie2[0] = '\0';
    w->origin[0] = '*';
    w->origin[1] = '\0';

    freez(w->user_agent); w->user_agent = NULL;
    if (w->auth_bearer_token) {
        freez(w->auth_bearer_token);
        w->auth_bearer_token = NULL;
    }

    w->mode = WEB_CLIENT_MODE_NORMAL;

    w->tcp_cork = 0;
    web_client_disable_donottrack(w);
    web_client_disable_tracking_required(w);
    web_client_disable_keepalive(w);
    w->decoded_url[0] = '\0';

    buffer_reset(w->response.header_output);
    buffer_reset(w->response.header);
    buffer_reset(w->response.data);
    w->response.rlen = 0;
    w->response.sent = 0;
    w->response.code = 0;

    w->header_parse_tries = 0;
    w->header_parse_last_size = 0;

    web_client_enable_wait_receive(w);
    web_client_disable_wait_send(w);

    w->response.zoutput = 0;

    // if we had enabled compression, release it
#ifdef NETDATA_WITH_ZLIB
    if(w->response.zinitialized) {
        debug(D_DEFLATE, "%llu: Freeing compression resources.", w->id);
        deflateEnd(&w->response.zstream);
        w->response.zsent = 0;
        w->response.zhave = 0;
        w->response.zstream.avail_in = 0;
        w->response.zstream.avail_out = 0;
        w->response.zstream.total_in = 0;
        w->response.zstream.total_out = 0;
        w->response.zinitialized = 0;
    }
#endif // NETDATA_WITH_ZLIB
}