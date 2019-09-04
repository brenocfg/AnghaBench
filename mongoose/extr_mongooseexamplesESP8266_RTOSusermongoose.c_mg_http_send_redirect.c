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
struct mg_str {scalar_t__ len; int /*<<< orphan*/  p; } ;
struct mg_connection {int dummy; } ;
typedef  int /*<<< orphan*/  bhead ;
typedef  int /*<<< orphan*/  bbody ;

/* Variables and functions */
 int /*<<< orphan*/  MG_FREE (char*) ; 
 int mg_asprintf (char**,int,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,char*,int) ; 
 int /*<<< orphan*/  mg_send_response_line (struct mg_connection*,int,char*) ; 

void mg_http_send_redirect(struct mg_connection *nc, int status_code,
                           const struct mg_str location,
                           const struct mg_str extra_headers) {
  char bbody[100], *pbody = bbody;
  int bl = mg_asprintf(&pbody, sizeof(bbody),
                       "<p>Moved <a href='%.*s'>here</a>.\r\n",
                       (int) location.len, location.p);
  char bhead[150], *phead = bhead;
  mg_asprintf(&phead, sizeof(bhead),
              "Location: %.*s\r\n"
              "Content-Type: text/html\r\n"
              "Content-Length: %d\r\n"
              "Cache-Control: no-cache\r\n"
              "%.*s%s",
              (int) location.len, location.p, bl, (int) extra_headers.len,
              extra_headers.p, (extra_headers.len > 0 ? "\r\n" : ""));
  mg_send_response_line(nc, status_code, phead);
  if (phead != bhead) MG_FREE(phead);
  mg_send(nc, pbody, bl);
  if (pbody != bbody) MG_FREE(pbody);
}