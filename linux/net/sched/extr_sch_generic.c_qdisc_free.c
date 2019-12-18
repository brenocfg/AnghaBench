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
struct Qdisc {int padded; int /*<<< orphan*/  cpu_qstats; int /*<<< orphan*/  cpu_bstats; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 scalar_t__ qdisc_is_percpu_stats (struct Qdisc*) ; 

void qdisc_free(struct Qdisc *qdisc)
{
	if (qdisc_is_percpu_stats(qdisc)) {
		free_percpu(qdisc->cpu_bstats);
		free_percpu(qdisc->cpu_qstats);
	}

	kfree((char *) qdisc - qdisc->padded);
}