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
struct hvsi_struct {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void print_state(struct hvsi_struct *hp)
{
#ifdef DEBUG
	static const char *state_names[] = {
		"HVSI_CLOSED",
		"HVSI_WAIT_FOR_VER_RESPONSE",
		"HVSI_WAIT_FOR_VER_QUERY",
		"HVSI_OPEN",
		"HVSI_WAIT_FOR_MCTRL_RESPONSE",
		"HVSI_FSP_DIED",
	};
	const char *name = (hp->state < ARRAY_SIZE(state_names))
		? state_names[hp->state] : "UNKNOWN";

	pr_debug("hvsi%i: state = %s\n", hp->index, name);
#endif /* DEBUG */
}