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
struct mg_mgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 int /*<<< orphan*/  s_http_address ; 
 int /*<<< orphan*/  s_mqtt_address ; 
 int /*<<< orphan*/  start_http_server (struct mg_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_mqtt_server (struct mg_mgr*,int /*<<< orphan*/ ) ; 

int main(void) {
  struct mg_mgr mgr;
  mg_mgr_init(&mgr, NULL);
  start_http_server(&mgr, s_http_address);
  start_mqtt_server(&mgr, s_mqtt_address);
  for (;;) {
    mg_mgr_poll(&mgr, 1000);
  }
}