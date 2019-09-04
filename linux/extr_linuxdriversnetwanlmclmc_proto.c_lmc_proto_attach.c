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
struct net_device {scalar_t__ addr_len; scalar_t__ hard_header_len; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {scalar_t__ if_type; struct net_device* lmc_device; } ;
typedef  TYPE_1__ lmc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_POINTOPOINT ; 
 scalar_t__ LMC_NET ; 
 int /*<<< orphan*/  lmc_trace (struct net_device*,char*) ; 

void lmc_proto_attach(lmc_softc_t *sc) /*FOLD00*/
{
    lmc_trace(sc->lmc_device, "lmc_proto_attach in");
    if (sc->if_type == LMC_NET) {
            struct net_device *dev = sc->lmc_device;
            /*
	     * They set a few basics because they don't use HDLC
             */
            dev->flags |= IFF_POINTOPOINT;
            dev->hard_header_len = 0;
            dev->addr_len = 0;
        }
    lmc_trace(sc->lmc_device, "lmc_proto_attach out");
}