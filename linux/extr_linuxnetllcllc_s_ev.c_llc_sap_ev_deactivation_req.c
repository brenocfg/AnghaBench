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
struct sk_buff {int dummy; } ;
struct llc_sap_state_ev {scalar_t__ type; scalar_t__ prim_type; } ;
struct llc_sap {int dummy; } ;

/* Variables and functions */
 scalar_t__ LLC_SAP_EV_DEACTIVATION_REQ ; 
 scalar_t__ LLC_SAP_EV_TYPE_SIMPLE ; 
 struct llc_sap_state_ev* llc_sap_ev (struct sk_buff*) ; 

int llc_sap_ev_deactivation_req(struct llc_sap *sap, struct sk_buff *skb)
{
	struct llc_sap_state_ev *ev = llc_sap_ev(skb);

	return ev->type == LLC_SAP_EV_TYPE_SIMPLE &&
	       ev->prim_type == LLC_SAP_EV_DEACTIVATION_REQ ? 0 : 1;
}