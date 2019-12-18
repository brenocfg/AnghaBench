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
typedef  size_t u32 ;
struct sfb_sched_data {TYPE_1__* bins; } ;
struct TYPE_2__ {int /*<<< orphan*/  perturbation; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void sfb_init_perturbation(u32 slot, struct sfb_sched_data *q)
{
	get_random_bytes(&q->bins[slot].perturbation,
			 sizeof(q->bins[slot].perturbation));
}