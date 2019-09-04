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
struct xsk_queue {scalar_t__ nentries; int /*<<< orphan*/  prod_tail; } ;

/* Variables and functions */
 scalar_t__ xskq_nb_free (struct xsk_queue*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline bool xskq_empty_desc(struct xsk_queue *q)
{
	return xskq_nb_free(q, q->prod_tail, q->nentries) == q->nentries;
}