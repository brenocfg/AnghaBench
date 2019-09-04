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
struct iucv_path {TYPE_1__* handler; } ;
struct iucv_message_complete {size_t ippathid; int /*<<< orphan*/  ipbfln2f; int /*<<< orphan*/  ipmsgtag; int /*<<< orphan*/  ipsrccls; int /*<<< orphan*/  iprmmsg; int /*<<< orphan*/  ipaudit; int /*<<< orphan*/  ipmsgid; int /*<<< orphan*/  ipflags1; } ;
struct iucv_message {int /*<<< orphan*/  length; int /*<<< orphan*/  tag; int /*<<< orphan*/  class; int /*<<< orphan*/  rmmsg; int /*<<< orphan*/  audit; int /*<<< orphan*/  id; int /*<<< orphan*/  flags; } ;
struct iucv_irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* message_complete ) (struct iucv_path*,struct iucv_message*) ;} ;

/* Variables and functions */
 struct iucv_path** iucv_path_table ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct iucv_path*,struct iucv_message*) ; 

__attribute__((used)) static void iucv_message_complete(struct iucv_irq_data *data)
{
	struct iucv_message_complete *imc = (void *) data;
	struct iucv_path *path = iucv_path_table[imc->ippathid];
	struct iucv_message msg;

	if (path && path->handler && path->handler->message_complete) {
		msg.flags = imc->ipflags1;
		msg.id = imc->ipmsgid;
		msg.audit = imc->ipaudit;
		memcpy(msg.rmmsg, imc->iprmmsg, 8);
		msg.class = imc->ipsrccls;
		msg.tag = imc->ipmsgtag;
		msg.length = imc->ipbfln2f;
		path->handler->message_complete(path, &msg);
	}
}