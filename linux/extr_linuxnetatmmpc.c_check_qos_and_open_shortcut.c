#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct mpoa_client {TYPE_8__* dev; TYPE_6__* eg_ops; } ;
struct TYPE_24__ {int traffic_class; } ;
struct TYPE_17__ {TYPE_7__ txtp; } ;
struct TYPE_18__ {int /*<<< orphan*/  in_dst_ip; } ;
struct TYPE_19__ {TYPE_1__ in_info; } ;
struct k_message {TYPE_14__ qos; int /*<<< orphan*/  type; TYPE_2__ content; } ;
struct atm_qos {int dummy; } ;
struct atm_mpoa_qos {TYPE_14__ qos; } ;
struct TYPE_26__ {TYPE_5__* shortcut; } ;
typedef  TYPE_9__ in_cache_entry ;
struct TYPE_16__ {TYPE_5__* shortcut; } ;
typedef  TYPE_10__ eg_cache_entry ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_25__ {int /*<<< orphan*/  name; } ;
struct TYPE_23__ {int /*<<< orphan*/  (* put ) (TYPE_10__*) ;TYPE_10__* (* get_by_src_ip ) (int /*<<< orphan*/ ,struct mpoa_client*) ;} ;
struct TYPE_20__ {int traffic_class; scalar_t__ max_pcr; } ;
struct TYPE_21__ {TYPE_3__ txtp; } ;
struct TYPE_22__ {TYPE_4__ qos; } ;

/* Variables and functions */
 int ATM_CBR ; 
 int ATM_UBR ; 
 int /*<<< orphan*/  OPEN_INGRESS_SVC ; 
 struct atm_mpoa_qos* atm_mpoa_search_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_14__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_to_mpoad (struct k_message*,struct mpoa_client*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 TYPE_10__* stub1 (int /*<<< orphan*/ ,struct mpoa_client*) ; 
 int /*<<< orphan*/  stub2 (TYPE_10__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_10__*) ; 

__attribute__((used)) static void check_qos_and_open_shortcut(struct k_message *msg,
					struct mpoa_client *client,
					in_cache_entry *entry)
{
	__be32 dst_ip = msg->content.in_info.in_dst_ip;
	struct atm_mpoa_qos *qos = atm_mpoa_search_qos(dst_ip);
	eg_cache_entry *eg_entry = client->eg_ops->get_by_src_ip(dst_ip, client);

	if (eg_entry && eg_entry->shortcut) {
		if (eg_entry->shortcut->qos.txtp.traffic_class &
		    msg->qos.txtp.traffic_class &
		    (qos ? qos->qos.txtp.traffic_class : ATM_UBR | ATM_CBR)) {
			if (eg_entry->shortcut->qos.txtp.traffic_class == ATM_UBR)
				entry->shortcut = eg_entry->shortcut;
			else if (eg_entry->shortcut->qos.txtp.max_pcr > 0)
				entry->shortcut = eg_entry->shortcut;
		}
		if (entry->shortcut) {
			dprintk("(%s) using egress SVC to reach %pI4\n",
				client->dev->name, &dst_ip);
			client->eg_ops->put(eg_entry);
			return;
		}
	}
	if (eg_entry != NULL)
		client->eg_ops->put(eg_entry);

	/* No luck in the egress cache we must open an ingress SVC */
	msg->type = OPEN_INGRESS_SVC;
	if (qos &&
	    (qos->qos.txtp.traffic_class == msg->qos.txtp.traffic_class)) {
		msg->qos = qos->qos;
		pr_info("(%s) trying to get a CBR shortcut\n",
			client->dev->name);
	} else
		memset(&msg->qos, 0, sizeof(struct atm_qos));
	msg_to_mpoad(msg, client);
}