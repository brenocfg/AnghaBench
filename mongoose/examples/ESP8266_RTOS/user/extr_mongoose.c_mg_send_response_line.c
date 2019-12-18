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
struct mg_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mg_mk_str (char const*) ; 
 int /*<<< orphan*/  mg_send_response_line_s (struct mg_connection*,int,int /*<<< orphan*/ ) ; 

void mg_send_response_line(struct mg_connection *nc, int status_code,
                           const char *extra_headers) {
  mg_send_response_line_s(nc, status_code, mg_mk_str(extra_headers));
}