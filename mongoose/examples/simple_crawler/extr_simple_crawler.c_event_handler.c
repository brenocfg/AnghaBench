#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct userdata {char* url; } ;
struct mg_connection {char* user_data; int /*<<< orphan*/  flags; } ;
struct http_message {int dummy; } ;

/* Variables and functions */
#define  MG_EV_CLOSE 130 
#define  MG_EV_CONNECT 129 
#define  MG_EV_HTTP_REPLY 128 
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  handle_reply (struct mg_connection*,struct http_message*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 char* strerror (int) ; 

__attribute__((used)) static void event_handler(struct mg_connection *nc, int event, void *data) {
  struct http_message *hm = (struct http_message *) data;
  int connect_status;

  switch (event) {
    case MG_EV_CONNECT:
      connect_status = *(int *) data;
      if (connect_status != 0) {
        printf("Error while loading page: %s, error: %s\n",
               ((struct userdata *) nc->user_data)->url,
               strerror(connect_status));
      }
      break;
    case MG_EV_CLOSE:
      free(((struct userdata *) nc->user_data)->url);
      free(nc->user_data);
      break;
    case MG_EV_HTTP_REPLY:
      handle_reply(nc, hm);
      nc->flags |= MG_F_SEND_AND_CLOSE;
      break;
    default:
      break;
  }
}