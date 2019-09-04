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
typedef  scalar_t__ time_t ;
struct mg_connection {int /*<<< orphan*/  send_mbuf; scalar_t__ last_io_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbuf_append (int /*<<< orphan*/ *,void const*,int) ; 
 scalar_t__ mg_time () ; 

void mg_send(struct mg_connection *nc, const void *buf, int len) {
  nc->last_io_time = (time_t) mg_time();
  mbuf_append(&nc->send_mbuf, buf, len);
}