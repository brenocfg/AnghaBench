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

/* Variables and functions */
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*,int,...) ; 
 int /*<<< orphan*/  mg_status_message (int) ; 
 int /*<<< orphan*/  mg_version_header ; 

void mg_send_response_line_s(struct mg_connection *nc, int status_code,
                             const struct mg_str extra_headers) {
  mg_printf(nc, "HTTP/1.1 %d %s\r\n", status_code,
            mg_status_message(status_code));
#ifndef MG_HIDE_SERVER_INFO
  mg_printf(nc, "Server: %s\r\n", mg_version_header);
#endif
  if (extra_headers.len > 0) {
    mg_printf(nc, "%.*s\r\n", (int) extra_headers.len, extra_headers.p);
  }
}