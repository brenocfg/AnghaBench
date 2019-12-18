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
struct mg_connection {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_DEBUG ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_send_head (struct mg_connection*,int,int /*<<< orphan*/ ,char*) ; 
 char* mg_status_message (int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void mg_http_send_error(struct mg_connection *nc, int code,
                        const char *reason) {
  if (!reason) reason = mg_status_message(code);
  LOG(LL_DEBUG, ("%p %d %s", nc, code, reason));
  mg_send_head(nc, code, strlen(reason),
               "Content-Type: text/plain\r\nConnection: close");
  mg_send(nc, reason, strlen(reason));
  nc->flags |= MG_F_SEND_AND_CLOSE;
}