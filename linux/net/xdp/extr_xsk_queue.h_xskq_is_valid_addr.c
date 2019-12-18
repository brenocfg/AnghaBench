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
typedef  scalar_t__ u64 ;
struct xsk_queue {scalar_t__ size; int /*<<< orphan*/  invalid_descs; } ;

/* Variables and functions */

__attribute__((used)) static inline bool xskq_is_valid_addr(struct xsk_queue *q, u64 addr)
{
	if (addr >= q->size) {
		q->invalid_descs++;
		return false;
	}

	return true;
}