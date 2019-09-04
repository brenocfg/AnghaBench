#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct mpoa_client {TYPE_5__* eg_ops; int /*<<< orphan*/ * eg_cache; TYPE_4__* in_cache; TYPE_3__* in_ops; } ;
struct k_message {int /*<<< orphan*/  type; } ;
struct atm_vcc {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  in_dst_ip; } ;
struct TYPE_14__ {TYPE_2__* prev; TYPE_4__* next; TYPE_1__ ctrl_info; struct atm_vcc* shortcut; } ;
typedef  TYPE_6__ in_cache_entry ;
typedef  int /*<<< orphan*/  eg_cache_entry ;
struct TYPE_13__ {int /*<<< orphan*/  (* put ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* get_by_vcc ) (struct atm_vcc*,struct mpoa_client*) ;} ;
struct TYPE_12__ {TYPE_2__* prev; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* put ) (TYPE_6__*) ;} ;
struct TYPE_10__ {TYPE_4__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  STOP_KEEP_ALIVE_SM ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_to_mpoad (struct k_message*,struct mpoa_client*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 
 int /*<<< orphan*/ * stub2 (struct atm_vcc*,struct mpoa_client*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcc_release_async (struct atm_vcc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void in_cache_remove_entry(in_cache_entry *entry,
				  struct mpoa_client *client)
{
	struct atm_vcc *vcc;
	struct k_message msg;

	vcc = entry->shortcut;
	dprintk("removing an ingress entry, ip = %pI4\n",
		&entry->ctrl_info.in_dst_ip);

	if (entry->prev != NULL)
		entry->prev->next = entry->next;
	else
		client->in_cache = entry->next;
	if (entry->next != NULL)
		entry->next->prev = entry->prev;
	client->in_ops->put(entry);
	if (client->in_cache == NULL && client->eg_cache == NULL) {
		msg.type = STOP_KEEP_ALIVE_SM;
		msg_to_mpoad(&msg, client);
	}

	/* Check if the egress side still uses this VCC */
	if (vcc != NULL) {
		eg_cache_entry *eg_entry = client->eg_ops->get_by_vcc(vcc,
								      client);
		if (eg_entry != NULL) {
			client->eg_ops->put(eg_entry);
			return;
		}
		vcc_release_async(vcc, -EPIPE);
	}
}