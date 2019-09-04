#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int u_int ;
struct TYPE_4__ {scalar_t__ rx1_fifo_start; scalar_t__ rbc_ram_start; } ;
struct fddi_mac_sf {scalar_t__ mac_info; void* mac_dest; void* mac_source; void* mac_fc; } ;
struct TYPE_5__ {TYPE_1__ fifo; struct fddi_mac_sf mac_sfb; } ;
struct TYPE_6__ {TYPE_2__ fp; } ;
struct s_smc {TYPE_3__ hw; } ;
struct fddi_mac {int dummy; } ;

/* Variables and functions */
 scalar_t__ BEACON_FRAME_OFF ; 
 scalar_t__ BEACON_INFO ; 
 scalar_t__ CLAIM_FRAME_OFF ; 
 scalar_t__ DBEACON_FRAME_OFF ; 
 scalar_t__ DBEACON_INFO ; 
 void* FC_BEACON ; 
 void* FC_CLAIM ; 
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_EACB ; 
 int /*<<< orphan*/  FM_RPXSF ; 
 int /*<<< orphan*/  FM_SABC ; 
 int /*<<< orphan*/  FM_SACL ; 
 int /*<<< orphan*/  FM_WPXSF ; 
 void* MA ; 
 int TX_DESCRIPTOR ; 
 int /*<<< orphan*/  copy_tx_mac (struct s_smc*,int,struct fddi_mac*,scalar_t__,int) ; 
 void* dbeacon_multi ; 
 void* null_addr ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_int (char*,int) ; 

__attribute__((used)) static void build_claim_beacon(struct s_smc *smc, u_long t_request)
{
	u_int	td ;
	int	len ;
	struct fddi_mac_sf *mac ;

	/*
	 * build claim packet
	 */
	len = 17 ;
	td = TX_DESCRIPTOR | ((((u_int)len-1)&3)<<27) ;
	mac = &smc->hw.fp.mac_sfb ;
	mac->mac_fc = FC_CLAIM ;
	/* DA == SA in claim frame */
	mac->mac_source = mac->mac_dest = MA ;
	/* 2's complement */
	set_int((char *)mac->mac_info,(int)t_request) ;

	copy_tx_mac(smc,td,(struct fddi_mac *)mac,
		smc->hw.fp.fifo.rbc_ram_start + CLAIM_FRAME_OFF,len) ;
	/* set CLAIM start pointer */
	outpw(FM_A(FM_SACL),smc->hw.fp.fifo.rbc_ram_start + CLAIM_FRAME_OFF) ;

	/*
	 * build beacon packet
	 */
	len = 17 ;
	td = TX_DESCRIPTOR | ((((u_int)len-1)&3)<<27) ;
	mac->mac_fc = FC_BEACON ;
	mac->mac_source = MA ;
	mac->mac_dest = null_addr ;		/* DA == 0 in beacon frame */
	set_int((char *) mac->mac_info,((int)BEACON_INFO<<24) + 0 ) ;

	copy_tx_mac(smc,td,(struct fddi_mac *)mac,
		smc->hw.fp.fifo.rbc_ram_start + BEACON_FRAME_OFF,len) ;
	/* set beacon start pointer */
	outpw(FM_A(FM_SABC),smc->hw.fp.fifo.rbc_ram_start + BEACON_FRAME_OFF) ;

	/*
	 * build directed beacon packet
	 * contains optional UNA
	 */
	len = 23 ;
	td = TX_DESCRIPTOR | ((((u_int)len-1)&3)<<27) ;
	mac->mac_fc = FC_BEACON ;
	mac->mac_source = MA ;
	mac->mac_dest = dbeacon_multi ;		/* multicast */
	set_int((char *) mac->mac_info,((int)DBEACON_INFO<<24) + 0 ) ;
	set_int((char *) mac->mac_info+4,0) ;
	set_int((char *) mac->mac_info+8,0) ;

	copy_tx_mac(smc,td,(struct fddi_mac *)mac,
		smc->hw.fp.fifo.rbc_ram_start + DBEACON_FRAME_OFF,len) ;

	/* end of claim/beacon queue */
	outpw(FM_A(FM_EACB),smc->hw.fp.fifo.rx1_fifo_start-1) ;

	outpw(FM_A(FM_WPXSF),0) ;
	outpw(FM_A(FM_RPXSF),0) ;
}