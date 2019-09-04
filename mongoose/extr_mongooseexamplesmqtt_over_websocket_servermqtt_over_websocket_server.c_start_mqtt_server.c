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
struct mg_mqtt_broker {int dummy; } ;
struct mg_mgr {int dummy; } ;
struct mg_connection {struct mg_mqtt_broker* user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mqtt_broker_init (struct mg_mqtt_broker*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_set_protocol_mqtt (struct mg_connection*) ; 
 int /*<<< orphan*/  mqtt_handler ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void start_mqtt_server(struct mg_mgr *mgr, const char *addr) {
  struct mg_connection *c;
  static struct mg_mqtt_broker brk;  // static is important - must not perish
  if ((c = mg_bind(mgr, addr, mqtt_handler)) == NULL) {
    fprintf(stderr, "Cannot start MQTT server on port [%s]\n", addr);
    exit(EXIT_FAILURE);
  }
  mg_mqtt_broker_init(&brk, NULL);
  c->user_data = &brk;
  mg_set_protocol_mqtt(c);
  printf("MQTT server started on %s\n", addr);
}