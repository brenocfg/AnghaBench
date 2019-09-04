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
 int /*<<< orphan*/  mg_printf_http_chunk (struct mg_connection*,char*,char const*) ; 
 int /*<<< orphan*/  mg_send_http_chunk (struct mg_connection*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_error_result(struct mg_connection *nc, const char *msg) {
  mg_printf_http_chunk(nc, "Error: %s", msg);
  mg_send_http_chunk(nc, "", 0); /* Send empty chunk, the end of response */
}