#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ ip4; } ;
struct TYPE_7__ {TYPE_2__ u_addr; } ;
struct netif {TYPE_3__ ip_addr; } ;
typedef  int /*<<< orphan*/  ppp_pcb ;
struct TYPE_8__ {int connected; int clean_close; int /*<<< orphan*/  pcb; } ;
typedef  TYPE_4__ ppp_if_obj_t ;

/* Variables and functions */
#define  PPPERR_CONNECT 130 
#define  PPPERR_NONE 129 
#define  PPPERR_USER 128 
 struct netif* ppp_netif (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ppp_status_cb(ppp_pcb *pcb, int err_code, void *ctx) {
    ppp_if_obj_t* self = ctx;
    struct netif *pppif = ppp_netif(self->pcb);

    switch (err_code) {
        case PPPERR_NONE:
            self->connected = (pppif->ip_addr.u_addr.ip4.addr != 0);
            break;
        case PPPERR_USER:
            self->clean_close = true;
            break;
        case PPPERR_CONNECT:
            self->connected = false;
            break;
        default:
            break;
    }
}