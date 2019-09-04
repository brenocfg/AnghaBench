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
struct Qdisc_ops {struct Qdisc_ops* next; } ;

/* Variables and functions */
 int ENOENT ; 
 struct Qdisc_ops* qdisc_base ; 
 int /*<<< orphan*/  qdisc_mod_lock ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int unregister_qdisc(struct Qdisc_ops *qops)
{
	struct Qdisc_ops *q, **qp;
	int err = -ENOENT;

	write_lock(&qdisc_mod_lock);
	for (qp = &qdisc_base; (q = *qp) != NULL; qp = &q->next)
		if (q == qops)
			break;
	if (q) {
		*qp = q->next;
		q->next = NULL;
		err = 0;
	}
	write_unlock(&qdisc_mod_lock);
	return err;
}