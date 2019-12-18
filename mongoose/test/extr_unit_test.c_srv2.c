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
struct mg_connection {scalar_t__ user_data; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {size_t len; scalar_t__ p; } ;
struct http_message {TYPE_1__ body; } ;
typedef  int /*<<< orphan*/  sig1 ;
typedef  int /*<<< orphan*/  cs_md5_ctx ;

/* Variables and functions */
#define  MG_EV_CONNECT 130 
#define  MG_EV_HTTP_CHUNK 129 
#define  MG_EV_HTTP_REPLY 128 
 int /*<<< orphan*/  MG_F_DELETE_CHUNK ; 
 int /*<<< orphan*/  cs_md5_final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs_md5_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcmp (unsigned char*,unsigned char*,int) ; 
 char* read_file (char*,size_t*) ; 

__attribute__((used)) static void srv2(struct mg_connection *c, int ev, void *ev_data) {
  static cs_md5_ctx c1, c2;
  struct http_message *hm = (struct http_message *) ev_data;

  switch (ev) {
    case MG_EV_CONNECT:
      cs_md5_init(&c1);
      cs_md5_init(&c2);
      break;
    case MG_EV_HTTP_CHUNK:
      cs_md5_update(&c1, (const unsigned char *) hm->body.p, hm->body.len);
      c->flags |= MG_F_DELETE_CHUNK;
      break;
    case MG_EV_HTTP_REPLY: {
      unsigned char sig1[16], sig2[sizeof(sig1)];
      size_t size;
      char *data = read_file("unit_test.c", &size);
      if (data != NULL) cs_md5_update(&c2, (const unsigned char *) data, size);
      free(data);
      cs_md5_final(sig1, &c1);
      cs_md5_final(sig2, &c2);
      *(int *) c->user_data = (memcmp(sig1, sig2, sizeof(sig1)) == 0) ? 1 : 2;
      break;
    }
  }
}