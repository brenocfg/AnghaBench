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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rxd_desc {int /*<<< orphan*/  va_hi; int /*<<< orphan*/  va_lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_RXD_BC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_RXD_CFI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_RXD_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_RXD_PKT_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_RXD_PRIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_RXD_RXFQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_RXD_RXP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_RXD_TO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_RXD_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_RXD_VLAN_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_RXD_VTAG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_rxdd(struct rxd_desc *rxdd, u32 rxd_val1, u16 len,
		       u16 rxd_vlan)
{
	DBG("ERROR: rxdd bc %d rxfq %d to %d type %d err %d rxp %d pkt_id %d vtag %d len %d vlan_id %d cfi %d prio %d va_lo %d va_hi %d\n",
	    GET_RXD_BC(rxd_val1), GET_RXD_RXFQ(rxd_val1), GET_RXD_TO(rxd_val1),
	    GET_RXD_TYPE(rxd_val1), GET_RXD_ERR(rxd_val1),
	    GET_RXD_RXP(rxd_val1), GET_RXD_PKT_ID(rxd_val1),
	    GET_RXD_VTAG(rxd_val1), len, GET_RXD_VLAN_ID(rxd_vlan),
	    GET_RXD_CFI(rxd_vlan), GET_RXD_PRIO(rxd_vlan), rxdd->va_lo,
	    rxdd->va_hi);
}