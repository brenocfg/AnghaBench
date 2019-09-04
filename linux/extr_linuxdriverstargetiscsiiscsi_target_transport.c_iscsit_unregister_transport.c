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
struct iscsit_transport {int /*<<< orphan*/  name; int /*<<< orphan*/  t_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transport_mutex ; 

void iscsit_unregister_transport(struct iscsit_transport *t)
{
	mutex_lock(&transport_mutex);
	list_del(&t->t_node);
	mutex_unlock(&transport_mutex);

	pr_debug("Unregistered iSCSI transport: %s\n", t->name);
}