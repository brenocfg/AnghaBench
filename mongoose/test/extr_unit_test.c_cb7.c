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
struct TYPE_4__ {scalar_t__ len; } ;
struct mg_connection {TYPE_2__ recv_mbuf; int /*<<< orphan*/  flags; scalar_t__ user_data; } ;
struct TYPE_3__ {size_t len; int /*<<< orphan*/  p; } ;
struct http_message {TYPE_1__ body; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  LL_INFO ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int MG_EV_HTTP_REPLY ; 
 int MG_EV_RECV ; 
 int /*<<< orphan*/  MG_F_CLOSE_IMMEDIATELY ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_argv_0 ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,size_t) ; 
 char* read_file (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void cb7(struct mg_connection *nc, int ev, void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;
  size_t size;
  char *data, *user_data = (char *) nc->user_data;

  if (ev == MG_EV_HTTP_REPLY) {
    /* Make sure that we've downloaded this executable, byte-to-byte */
    data = read_file(g_argv_0, &size);
    DBG(("file %s, size %d; got %d", g_argv_0, (int) size, (int) hm->body.len));
    if (data != NULL && size == hm->body.len &&
        memcmp(hm->body.p, data, size) == 0) {
      strcpy(user_data, "success");
    } else {
      strcpy(user_data, "fail");
    }
    free(data);
    nc->flags |= MG_F_CLOSE_IMMEDIATELY;
  } else if (ev == MG_EV_RECV) {
#if 0
    LOG(LL_INFO, ("%d", (int) nc->recv_mbuf.len));
#endif
  }
}