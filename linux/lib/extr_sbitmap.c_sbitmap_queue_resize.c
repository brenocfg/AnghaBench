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
struct sbitmap_queue {int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbitmap_queue_update_wake_batch (struct sbitmap_queue*,unsigned int) ; 
 int /*<<< orphan*/  sbitmap_resize (int /*<<< orphan*/ *,unsigned int) ; 

void sbitmap_queue_resize(struct sbitmap_queue *sbq, unsigned int depth)
{
	sbitmap_queue_update_wake_batch(sbq, depth);
	sbitmap_resize(&sbq->sb, depth);
}