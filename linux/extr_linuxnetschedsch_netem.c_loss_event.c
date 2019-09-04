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
struct netem_sched_data {int loss_model; int /*<<< orphan*/  loss_cor; int /*<<< orphan*/  loss; } ;

/* Variables and functions */
#define  CLG_4_STATES 130 
#define  CLG_GILB_ELL 129 
#define  CLG_RANDOM 128 
 int /*<<< orphan*/  get_crandom (int /*<<< orphan*/ *) ; 
 int loss_4state (struct netem_sched_data*) ; 
 int loss_gilb_ell (struct netem_sched_data*) ; 

__attribute__((used)) static bool loss_event(struct netem_sched_data *q)
{
	switch (q->loss_model) {
	case CLG_RANDOM:
		/* Random packet drop 0 => none, ~0 => all */
		return q->loss && q->loss >= get_crandom(&q->loss_cor);

	case CLG_4_STATES:
		/* 4state loss model algorithm (used also for GI model)
		* Extracts a value from the markov 4 state loss generator,
		* if it is 1 drops a packet and if needed writes the event in
		* the kernel logs
		*/
		return loss_4state(q);

	case CLG_GILB_ELL:
		/* Gilbert-Elliot loss model algorithm
		* Extracts a value from the Gilbert-Elliot loss generator,
		* if it is 1 drops a packet and if needed writes the event in
		* the kernel logs
		*/
		return loss_gilb_ell(q);
	}

	return false;	/* not reached */
}