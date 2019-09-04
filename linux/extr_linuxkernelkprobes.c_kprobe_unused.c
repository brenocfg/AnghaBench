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
struct kprobe {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ kprobe_aggrprobe (struct kprobe*) ; 
 scalar_t__ kprobe_disabled (struct kprobe*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int kprobe_unused(struct kprobe *p)
{
	return kprobe_aggrprobe(p) && kprobe_disabled(p) &&
	       list_empty(&p->list);
}