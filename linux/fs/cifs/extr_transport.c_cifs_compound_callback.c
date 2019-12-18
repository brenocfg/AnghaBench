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
struct mid_q_entry {int /*<<< orphan*/  optype; struct TCP_Server_Info* server; } ;
struct cifs_credits {int /*<<< orphan*/  instance; int /*<<< orphan*/  value; } ;
struct TCP_Server_Info {int /*<<< orphan*/  reconnect_instance; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_credits ) (struct mid_q_entry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  add_credits (struct TCP_Server_Info*,struct cifs_credits*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mid_q_entry*) ; 

__attribute__((used)) static void
cifs_compound_callback(struct mid_q_entry *mid)
{
	struct TCP_Server_Info *server = mid->server;
	struct cifs_credits credits;

	credits.value = server->ops->get_credits(mid);
	credits.instance = server->reconnect_instance;

	add_credits(server, &credits, mid->optype);
}