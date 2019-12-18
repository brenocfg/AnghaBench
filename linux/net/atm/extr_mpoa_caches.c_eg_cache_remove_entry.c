#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mpoa_client {TYPE_4__* in_ops; TYPE_3__* eg_cache; int /*<<< orphan*/ * in_cache; TYPE_2__* eg_ops; } ;
struct k_message {int /*<<< orphan*/  type; } ;
struct atm_vcc {int dummy; } ;
typedef  int /*<<< orphan*/  in_cache_entry ;
struct TYPE_12__ {TYPE_1__* prev; TYPE_3__* next; struct atm_vcc* shortcut; } ;
typedef  TYPE_5__ eg_cache_entry ;
struct TYPE_11__ {int /*<<< orphan*/  (* put ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* get_by_vcc ) (struct atm_vcc*,struct mpoa_client*) ;} ;
struct TYPE_10__ {TYPE_1__* prev; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* put ) (TYPE_5__*) ;} ;
struct TYPE_8__ {TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  STOP_KEEP_ALIVE_SM ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  msg_to_mpoad (struct k_message*,struct mpoa_client*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/ * stub2 (struct atm_vcc*,struct mpoa_client*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcc_release_async (struct atm_vcc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eg_cache_remove_entry(eg_cache_entry *entry,
				  struct mpoa_client *client)
{
	struct atm_vcc *vcc;
	struct k_message msg;

	vcc = entry->shortcut;
	dprintk("removing an egress entry.\n");
	if (entry->prev != NULL)
		entry->prev->next = entry->next;
	else
		client->eg_cache = entry->next;
	if (entry->next != NULL)
		entry->next->prev = entry->prev;
	client->eg_ops->put(entry);
	if (client->in_cache == NULL && client->eg_cache == NULL) {
		msg.type = STOP_KEEP_ALIVE_SM;
		msg_to_mpoad(&msg, client);
	}

	/* Check if the ingress side still uses this VCC */
	if (vcc != NULL) {
		in_cache_entry *in_entry = client->in_ops->get_by_vcc(vcc, client);
		if (in_entry != NULL) {
			client->in_ops->put(in_entry);
			return;
		}
		vcc_release_async(vcc, -EPIPE);
	}
}