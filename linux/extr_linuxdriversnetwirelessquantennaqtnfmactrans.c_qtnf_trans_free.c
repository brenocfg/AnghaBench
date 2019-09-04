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
struct qtnf_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  qtnf_trans_free_events (struct qtnf_bus*) ; 

void qtnf_trans_free(struct qtnf_bus *bus)
{
	if (!bus) {
		pr_err("invalid bus pointer\n");
		return;
	}

	qtnf_trans_free_events(bus);
}