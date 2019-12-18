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
 int /*<<< orphan*/  mg_send_websocket_handshake3v (struct mg_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mg_send_websocket_handshake3(struct mg_connection *nc, const char *path,
                                  const char *host, const char *protocol,
                                  const char *extra_headers, const char *user,
                                  const char *pass) {
  mg_send_websocket_handshake3v(nc, mg_mk_str(path), mg_mk_str(host),
                                mg_mk_str(protocol), mg_mk_str(extra_headers),
                                mg_mk_str(user), mg_mk_str(pass));
}