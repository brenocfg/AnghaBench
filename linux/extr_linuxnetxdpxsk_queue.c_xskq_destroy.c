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
struct xsk_queue {int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct xsk_queue*) ; 
 int /*<<< orphan*/  page_frag_free (int /*<<< orphan*/ ) ; 

void xskq_destroy(struct xsk_queue *q)
{
	if (!q)
		return;

	page_frag_free(q->ring);
	kfree(q);
}