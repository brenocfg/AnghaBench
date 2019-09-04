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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ size; } ;
struct xsk_queue {int /*<<< orphan*/  invalid_descs; TYPE_1__ umem_props; } ;

/* Variables and functions */

__attribute__((used)) static inline bool xskq_is_valid_addr(struct xsk_queue *q, u64 addr)
{
	if (addr >= q->umem_props.size) {
		q->invalid_descs++;
		return false;
	}

	return true;
}