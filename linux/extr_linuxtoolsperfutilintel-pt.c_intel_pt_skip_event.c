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
struct TYPE_2__ {scalar_t__ initial_skip; } ;
struct intel_pt {TYPE_1__ synth_opts; int /*<<< orphan*/  num_events; } ;

/* Variables and functions */

__attribute__((used)) static inline bool intel_pt_skip_event(struct intel_pt *pt)
{
	return pt->synth_opts.initial_skip &&
	       pt->num_events++ < pt->synth_opts.initial_skip;
}