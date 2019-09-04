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
struct mg_str {int len; int /*<<< orphan*/  p; } ;
struct mg_serve_http_opts {char* document_root; } ;
struct mg_http_multipart_part {int /*<<< orphan*/  file_name; } ;
struct mg_connection {void* user_data; int /*<<< orphan*/  ev_timer_time; int /*<<< orphan*/  handler; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  p; scalar_t__ len; } ;
struct TYPE_3__ {int /*<<< orphan*/  p; scalar_t__ len; } ;
struct http_message {TYPE_2__ uri; TYPE_1__ method; } ;
typedef  int /*<<< orphan*/  opts ;
typedef  int /*<<< orphan*/  cs_stat_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 double DATA_COLLECTION_INTERVAL_MS ; 
 int /*<<< orphan*/  LL_INFO ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
#define  MG_EV_ACCEPT 136 
#define  MG_EV_CLOSE 135 
#define  MG_EV_HTTP_MULTIPART_REQUEST 134 
#define  MG_EV_HTTP_PART_BEGIN 133 
#define  MG_EV_HTTP_PART_DATA 132 
#define  MG_EV_HTTP_PART_END 131 
#define  MG_EV_HTTP_REQUEST 130 
#define  MG_EV_TIMER 129 
#define  MG_EV_WEBSOCKET_HANDSHAKE_DONE 128 
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 int MG_SOCK_STRINGIFY_IP ; 
 int MG_SOCK_STRINGIFY_PORT ; 
 int MG_SOCK_STRINGIFY_REMOTE ; 
 intptr_t atoi (char*) ; 
 int /*<<< orphan*/  data_collect () ; 
 int /*<<< orphan*/  data_conn_handler ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct mg_serve_http_opts*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mg_conn_addr_to_str (struct mg_connection*,char*,int,int) ; 
 int /*<<< orphan*/  mg_file_upload_handler (struct mg_connection*,int,void*,int /*<<< orphan*/ ) ; 
 struct mg_str* mg_get_http_header (struct http_message*,char*) ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_serve_http (struct mg_connection*,struct http_message*,struct mg_serve_http_opts) ; 
 int /*<<< orphan*/  mg_stat (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_time () ; 
 int /*<<< orphan*/  mg_vcmp (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upload_fname ; 
 int /*<<< orphan*/  upload_form ; 

__attribute__((used)) static void mg_ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  switch (ev) {
    case MG_EV_ACCEPT: {
      char addr[32];
      mg_conn_addr_to_str(nc, addr, sizeof(addr), MG_SOCK_STRINGIFY_REMOTE |
                                                      MG_SOCK_STRINGIFY_IP |
                                                      MG_SOCK_STRINGIFY_PORT);
      LOG(LL_INFO, ("%p conn from %s", nc, addr));
      break;
    }
    case MG_EV_HTTP_REQUEST: {
      char addr[32];
      struct http_message *hm = (struct http_message *) ev_data;
      cs_stat_t st;
      mg_conn_addr_to_str(nc, addr, sizeof(addr), MG_SOCK_STRINGIFY_REMOTE |
                                                      MG_SOCK_STRINGIFY_IP |
                                                      MG_SOCK_STRINGIFY_PORT);
      LOG(LL_INFO,
          ("HTTP request from %s: %.*s %.*s", addr, (int) hm->method.len,
           hm->method.p, (int) hm->uri.len, hm->uri.p));
      if (mg_vcmp(&hm->uri, "/upload") == 0 ||
          (mg_vcmp(&hm->uri, "/") == 0 && mg_stat("SL:index.html", &st) != 0)) {
        mg_send(nc, upload_form, strlen(upload_form));
        nc->flags |= MG_F_SEND_AND_CLOSE;
        break;
      }
      struct mg_serve_http_opts opts;
      memset(&opts, 0, sizeof(opts));
      opts.document_root = "SL:";
      mg_serve_http(nc, hm, opts);
      break;
    }
    case MG_EV_CLOSE: {
      LOG(LL_INFO, ("%p closed", nc));
      break;
    }
    case MG_EV_WEBSOCKET_HANDSHAKE_DONE: {
      LOG(LL_INFO, ("%p switching to data mode", nc));
      nc->handler = data_conn_handler;
      nc->ev_timer_time = mg_time(); /* Immediately */
      break;
    }
    case MG_EV_TIMER: {
      data_collect();
      nc->ev_timer_time = mg_time() + (DATA_COLLECTION_INTERVAL_MS * 0.001);
      break;
    }
    /* SimpleLink FS requires pre-declaring max file size. We use Content-Length
     * for that purpose - it will not exactly match file size, but is guaranteed
     * to exceed it and should be close enough. */
    case MG_EV_HTTP_MULTIPART_REQUEST: {
      struct http_message *hm = (struct http_message *) ev_data;
      struct mg_str *cl_header = mg_get_http_header(hm, "Content-Length");
      intptr_t cl = -1;
      if (cl_header != NULL && cl_header->len < 20) {
        char buf[20];
        memcpy(buf, cl_header->p, cl_header->len);
        buf[cl_header->len] = '\0';
        cl = atoi(buf);
        if (cl < 0) cl = -1;
      }
      nc->user_data = (void *) cl;
      break;
    }
    case MG_EV_HTTP_PART_BEGIN:
    case MG_EV_HTTP_PART_DATA:
    case MG_EV_HTTP_PART_END: {
      struct mg_http_multipart_part *mp =
          (struct mg_http_multipart_part *) ev_data;
      if (ev == MG_EV_HTTP_PART_BEGIN) {
        LOG(LL_INFO, ("Begin file upload: %s", mp->file_name));
      } else if (ev == MG_EV_HTTP_PART_END) {
        LOG(LL_INFO, ("End file upload: %s", mp->file_name));
      }
      mg_file_upload_handler(nc, ev, ev_data, upload_fname);
    }
  }
}