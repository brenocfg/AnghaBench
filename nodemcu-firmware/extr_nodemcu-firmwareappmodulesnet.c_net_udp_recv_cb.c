#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16_t ;
struct udp_pcb {int dummy; } ;
struct pbuf {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; scalar_t__ self_ref; int /*<<< orphan*/  pcb; } ;
typedef  TYPE_1__ lnet_userdata ;
typedef  int /*<<< orphan*/  ip_addr_t ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 scalar_t__ TYPE_UDP_SOCKET ; 
 int /*<<< orphan*/  net_recv_cb (TYPE_1__*,struct pbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 

__attribute__((used)) static void net_udp_recv_cb(void *arg, struct udp_pcb *pcb, struct pbuf *p, ip_addr_t *addr, u16_t port) {
  lnet_userdata *ud = (lnet_userdata*)arg;
  if (!ud || !ud->pcb || ud->type != TYPE_UDP_SOCKET || ud->self_ref == LUA_NOREF) {
    if (p) pbuf_free(p);
    return;
  }
  net_recv_cb(ud, p, addr, port);
}