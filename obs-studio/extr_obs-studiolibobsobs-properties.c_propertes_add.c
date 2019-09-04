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
struct obs_property {struct obs_property* next; } ;
struct obs_properties {struct obs_property** last; } ;

/* Variables and functions */

__attribute__((used)) static inline void propertes_add(struct obs_properties *props,
		struct obs_property *p)
{
	*props->last = p;
	props->last = &p->next;
}