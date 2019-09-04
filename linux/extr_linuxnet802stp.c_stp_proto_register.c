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
struct stp_proto {size_t* group_address; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t GARP_ADDR_MIN ; 
 int /*<<< orphan*/  LLC_SAP_BSPAN ; 
 int /*<<< orphan*/ * garp_protos ; 
 scalar_t__ is_zero_ether_addr (size_t*) ; 
 int /*<<< orphan*/  llc_sap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct stp_proto const*) ; 
 int /*<<< orphan*/  sap ; 
 int /*<<< orphan*/  sap_registered ; 
 int /*<<< orphan*/  stp_pdu_rcv ; 
 int /*<<< orphan*/  stp_proto ; 
 int /*<<< orphan*/  stp_proto_mutex ; 

int stp_proto_register(const struct stp_proto *proto)
{
	int err = 0;

	mutex_lock(&stp_proto_mutex);
	if (sap_registered++ == 0) {
		sap = llc_sap_open(LLC_SAP_BSPAN, stp_pdu_rcv);
		if (!sap) {
			err = -ENOMEM;
			goto out;
		}
	}
	if (is_zero_ether_addr(proto->group_address))
		rcu_assign_pointer(stp_proto, proto);
	else
		rcu_assign_pointer(garp_protos[proto->group_address[5] -
					       GARP_ADDR_MIN], proto);
out:
	mutex_unlock(&stp_proto_mutex);
	return err;
}