#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rlen; TYPE_3__* data; scalar_t__ sent; void* code; } ;
struct TYPE_7__ {scalar_t__ tv_sec; } ;
struct web_client {int mode; int /*<<< orphan*/  id; TYPE_1__ response; TYPE_2__ tv_ready; int /*<<< orphan*/  last_url; int /*<<< orphan*/  decoded_url; TYPE_2__ tv_in; } ;
struct TYPE_8__ {scalar_t__ len; scalar_t__ date; int /*<<< orphan*/  buffer; int /*<<< orphan*/  contenttype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT_TEXT_HTML ; 
 int /*<<< orphan*/  CT_TEXT_PLAIN ; 
 int /*<<< orphan*/  D_WEB_CLIENT ; 
 int /*<<< orphan*/  D_WEB_CLIENT_ACCESS ; 
 void* HTTP_RESP_BAD_REQUEST ; 
 void* HTTP_RESP_MOVED_PERM ; 
 void* HTTP_RESP_OK ; 
#define  HTTP_VALIDATION_INCOMPLETE 136 
#define  HTTP_VALIDATION_MALFORMED_URL 135 
#define  HTTP_VALIDATION_NOT_SUPPORTED 134 
#define  HTTP_VALIDATION_OK 133 
#define  HTTP_VALIDATION_REDIRECT 132 
 scalar_t__ NETDATA_WEB_REQUEST_MAX_SIZE ; 
#define  WEB_CLIENT_MODE_FILECOPY 131 
#define  WEB_CLIENT_MODE_NORMAL 130 
#define  WEB_CLIENT_MODE_OPTIONS 129 
#define  WEB_CLIENT_MODE_STREAM 128 
 int /*<<< orphan*/  buffer_flush (TYPE_3__*) ; 
 int /*<<< orphan*/  buffer_sprintf (TYPE_3__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  buffer_strcat (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ,int) ; 
 int http_request_validate (struct web_client*) ; 
 int /*<<< orphan*/  localhost ; 
 int /*<<< orphan*/  now_realtime_timeval (TYPE_2__*) ; 
 void* rrdpush_receiver_thread_spawn (int /*<<< orphan*/ ,struct web_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  web_client_can_access_badges (struct web_client*) ; 
 int /*<<< orphan*/  web_client_can_access_dashboard (struct web_client*) ; 
 int /*<<< orphan*/  web_client_can_access_mgmt (struct web_client*) ; 
 int /*<<< orphan*/  web_client_can_access_netdataconf (struct web_client*) ; 
 int /*<<< orphan*/  web_client_can_access_registry (struct web_client*) ; 
 int /*<<< orphan*/  web_client_can_access_stream (struct web_client*) ; 
 int /*<<< orphan*/  web_client_disable_wait_send (struct web_client*) ; 
 int /*<<< orphan*/  web_client_enable_wait_receive (struct web_client*) ; 
 int /*<<< orphan*/  web_client_enable_wait_send (struct web_client*) ; 
 int /*<<< orphan*/  web_client_permission_denied (struct web_client*) ; 
 void* web_client_process_url (int /*<<< orphan*/ ,struct web_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  web_client_send_http_header (struct web_client*) ; 

void web_client_process_request(struct web_client *w) {

    // start timing us
    now_realtime_timeval(&w->tv_in);

    switch(http_request_validate(w)) {
        case HTTP_VALIDATION_OK:
            switch(w->mode) {
                case WEB_CLIENT_MODE_STREAM:
                    if(unlikely(!web_client_can_access_stream(w))) {
                        web_client_permission_denied(w);
                        return;
                    }

                    w->response.code = rrdpush_receiver_thread_spawn(localhost, w, w->decoded_url);
                    return;

                case WEB_CLIENT_MODE_OPTIONS:
                    if(unlikely(
                            !web_client_can_access_dashboard(w) &&
                            !web_client_can_access_registry(w) &&
                            !web_client_can_access_badges(w) &&
                            !web_client_can_access_mgmt(w) &&
                            !web_client_can_access_netdataconf(w)
                    )) {
                        web_client_permission_denied(w);
                        break;
                    }

                    w->response.data->contenttype = CT_TEXT_PLAIN;
                    buffer_flush(w->response.data);
                    buffer_strcat(w->response.data, "OK");
                    w->response.code = HTTP_RESP_OK;
                    break;

                case WEB_CLIENT_MODE_FILECOPY:
                case WEB_CLIENT_MODE_NORMAL:
                    if(unlikely(
                            !web_client_can_access_dashboard(w) &&
                            !web_client_can_access_registry(w) &&
                            !web_client_can_access_badges(w) &&
                            !web_client_can_access_mgmt(w) &&
                            !web_client_can_access_netdataconf(w)
                    )) {
                        web_client_permission_denied(w);
                        break;
                    }

                    w->response.code = web_client_process_url(localhost, w, w->decoded_url);
                    break;
            }
            break;

        case HTTP_VALIDATION_INCOMPLETE:
            if(w->response.data->len > NETDATA_WEB_REQUEST_MAX_SIZE) {
                strcpy(w->last_url, "too big request");

                debug(D_WEB_CLIENT_ACCESS, "%llu: Received request is too big (%zu bytes).", w->id, w->response.data->len);

                buffer_flush(w->response.data);
                buffer_sprintf(w->response.data, "Received request is too big  (%zu bytes).\r\n", w->response.data->len);
                w->response.code = HTTP_RESP_BAD_REQUEST;
            }
            else {
                // wait for more data
                return;
            }
            break;
#ifdef ENABLE_HTTPS
        case HTTP_VALIDATION_REDIRECT:
        {
            buffer_flush(w->response.data);
            w->response.data->contenttype = CT_TEXT_HTML;
            buffer_strcat(w->response.data, "<!DOCTYPE html><!-- SPDX-License-Identifier: GPL-3.0-or-later --><html><body onload=\"window.location.href ='https://'+ window.location.hostname + ':' + window.location.port +  window.location.pathname\">Redirecting to safety connection, case your browser does not support redirection, please click <a onclick=\"window.location.href ='https://'+ window.location.hostname + ':' + window.location.port +  window.location.pathname\">here</a>.</body></html>");
            w->response.code = HTTP_RESP_MOVED_PERM;
            break;
        }
#endif
        case HTTP_VALIDATION_MALFORMED_URL:
            debug(D_WEB_CLIENT_ACCESS, "%llu: URL parsing failed (malformed URL). Cannot understand '%s'.", w->id, w->response.data->buffer);

            buffer_flush(w->response.data);
            buffer_strcat(w->response.data, "URL not valid. I don't understand you...\r\n");
            w->response.code = HTTP_RESP_BAD_REQUEST;
            break;
        case HTTP_VALIDATION_NOT_SUPPORTED:
            debug(D_WEB_CLIENT_ACCESS, "%llu: Cannot understand '%s'.", w->id, w->response.data->buffer);

            buffer_flush(w->response.data);
            buffer_strcat(w->response.data, "I don't understand you...\r\n");
            w->response.code = HTTP_RESP_BAD_REQUEST;
            break;
    }

    // keep track of the time we done processing
    now_realtime_timeval(&w->tv_ready);

    w->response.sent = 0;

    // set a proper last modified date
    if(unlikely(!w->response.data->date))
        w->response.data->date = w->tv_ready.tv_sec;

    web_client_send_http_header(w);

    // enable sending immediately if we have data
    if(w->response.data->len) web_client_enable_wait_send(w);
    else web_client_disable_wait_send(w);

    switch(w->mode) {
        case WEB_CLIENT_MODE_STREAM:
            debug(D_WEB_CLIENT, "%llu: STREAM done.", w->id);
            break;

        case WEB_CLIENT_MODE_OPTIONS:
            debug(D_WEB_CLIENT, "%llu: Done preparing the OPTIONS response. Sending data (%zu bytes) to client.", w->id, w->response.data->len);
            break;

        case WEB_CLIENT_MODE_NORMAL:
            debug(D_WEB_CLIENT, "%llu: Done preparing the response. Sending data (%zu bytes) to client.", w->id, w->response.data->len);
            break;

        case WEB_CLIENT_MODE_FILECOPY:
            if(w->response.rlen) {
                debug(D_WEB_CLIENT, "%llu: Done preparing the response. Will be sending data file of %zu bytes to client.", w->id, w->response.rlen);
                web_client_enable_wait_receive(w);

                /*
                // utilize the kernel sendfile() for copying the file to the socket.
                // this block of code can be commented, without anything missing.
                // when it is commented, the program will copy the data using async I/O.
                {
                    long len = sendfile(w->ofd, w->ifd, NULL, w->response.data->rbytes);
                    if(len != w->response.data->rbytes)
                        error("%llu: sendfile() should copy %ld bytes, but copied %ld. Falling back to manual copy.", w->id, w->response.data->rbytes, len);
                    else
                        web_client_request_done(w);
                }
                */
            }
            else
                debug(D_WEB_CLIENT, "%llu: Done preparing the response. Will be sending an unknown amount of bytes to client.", w->id);
            break;

        default:
            fatal("%llu: Unknown client mode %u.", w->id, w->mode);
            break;
    }
}