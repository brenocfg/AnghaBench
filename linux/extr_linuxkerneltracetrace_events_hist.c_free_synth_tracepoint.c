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
struct tracepoint {struct tracepoint* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tracepoint*) ; 

__attribute__((used)) static void free_synth_tracepoint(struct tracepoint *tp)
{
	if (!tp)
		return;

	kfree(tp->name);
	kfree(tp);
}