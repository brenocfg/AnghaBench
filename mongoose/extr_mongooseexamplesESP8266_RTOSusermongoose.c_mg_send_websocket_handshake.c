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
struct mg_str {int dummy; } ;
struct mg_connection {int dummy; } ;

/* Variables and functions */
 struct mg_str MG_NULL_STR ; 
 int /*<<< orphan*/  mg_mk_str (char const*) ; 
 int /*<<< orphan*/  mg_send_websocket_handshake3v (struct mg_connection*,int /*<<< orphan*/ ,struct mg_str,struct mg_str,int /*<<< orphan*/ ,struct mg_str,struct mg_str) ; 

void mg_send_websocket_handshake(struct mg_connection *nc, const char *path,
                                 const char *extra_headers) {
  struct mg_str null_str = MG_NULL_STR;
  mg_send_websocket_handshake3v(
      nc, mg_mk_str(path), null_str /* host */, null_str /* protocol */,
      mg_mk_str(extra_headers), null_str /* user */, null_str /* pass */);
}