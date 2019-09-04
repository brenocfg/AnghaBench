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
struct mg_connection {int /*<<< orphan*/  proto_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  dns_handler ; 

void mg_set_protocol_dns(struct mg_connection *nc) {
  nc->proto_handler = dns_handler;
}