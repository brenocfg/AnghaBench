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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct qfq_aggregate {int inv_w; scalar_t__ S; scalar_t__ F; scalar_t__ budget; scalar_t__ initial_budget; int /*<<< orphan*/  budgetmax; } ;

/* Variables and functions */
 scalar_t__ min (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void charge_actual_service(struct qfq_aggregate *agg)
{
	/* Compute the service received by the aggregate, taking into
	 * account that, after decreasing the number of classes in
	 * agg, it may happen that
	 * agg->initial_budget - agg->budget > agg->bugdetmax
	 */
	u32 service_received = min(agg->budgetmax,
				   agg->initial_budget - agg->budget);

	agg->F = agg->S + (u64)service_received * agg->inv_w;
}