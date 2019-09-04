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
struct mg_connection {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  p; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  p; } ;
struct http_message {TYPE_2__ body; TYPE_1__ message; } ;

/* Variables and functions */
#define  MG_EV_CLOSE 130 
#define  MG_EV_CONNECT 129 
#define  MG_EV_HTTP_REPLY 128 
 int /*<<< orphan*/  MG_F_CLOSE_IMMEDIATELY ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int s_exit_flag ; 
 int /*<<< orphan*/  s_show_headers ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int) ; 

__attribute__((used)) static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;

  switch (ev) {
    case MG_EV_CONNECT:
      if (*(int *) ev_data != 0) {
        fprintf(stderr, "connect() failed: %s\n", strerror(*(int *) ev_data));
        s_exit_flag = 1;
      }
      break;
    case MG_EV_HTTP_REPLY:
      nc->flags |= MG_F_CLOSE_IMMEDIATELY;
      if (s_show_headers) {
        fwrite(hm->message.p, 1, hm->message.len, stdout);
      } else {
        fwrite(hm->body.p, 1, hm->body.len, stdout);
      }
      putchar('\n');
      s_exit_flag = 1;
      break;
    case MG_EV_CLOSE:
      if (s_exit_flag == 0) {
        printf("Server closed connection\n");
        s_exit_flag = 1;
      }
      break;
    default:
      break;
  }
}