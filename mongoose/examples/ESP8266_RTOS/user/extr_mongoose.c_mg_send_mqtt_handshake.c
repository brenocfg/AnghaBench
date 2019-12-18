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
struct mg_send_mqtt_handshake_opts {int dummy; } ;
struct mg_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mg_send_mqtt_handshake_opt (struct mg_connection*,char const*,struct mg_send_mqtt_handshake_opts) ; 

void mg_send_mqtt_handshake(struct mg_connection *nc, const char *client_id) {
  static struct mg_send_mqtt_handshake_opts opts;
  mg_send_mqtt_handshake_opt(nc, client_id, opts);
}