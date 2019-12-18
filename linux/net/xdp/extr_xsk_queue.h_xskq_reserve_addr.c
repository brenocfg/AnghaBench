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
struct xsk_queue {int /*<<< orphan*/  prod_head; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ xskq_nb_free (struct xsk_queue*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int xskq_reserve_addr(struct xsk_queue *q)
{
	if (xskq_nb_free(q, q->prod_head, 1) == 0)
		return -ENOSPC;

	/* A, matches D */
	q->prod_head++;
	return 0;
}