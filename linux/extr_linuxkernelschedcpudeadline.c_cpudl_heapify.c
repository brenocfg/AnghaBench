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
struct cpudl {TYPE_1__* elements; } ;
struct TYPE_2__ {int /*<<< orphan*/  dl; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpudl_heapify_down (struct cpudl*,int) ; 
 int /*<<< orphan*/  cpudl_heapify_up (struct cpudl*,int) ; 
 scalar_t__ dl_time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t parent (int) ; 

__attribute__((used)) static void cpudl_heapify(struct cpudl *cp, int idx)
{
	if (idx > 0 && dl_time_before(cp->elements[parent(idx)].dl,
				cp->elements[idx].dl))
		cpudl_heapify_up(cp, idx);
	else
		cpudl_heapify_down(cp, idx);
}