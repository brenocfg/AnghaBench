#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mg_iface {TYPE_1__* mgr; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  mg_socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mg_socket_if_init(struct mg_iface *iface) {
  (void) iface;
  DBG(("%p using select()", iface->mgr));
#if MG_ENABLE_BROADCAST
  mg_socketpair(iface->mgr->ctl, SOCK_DGRAM);
#endif
}