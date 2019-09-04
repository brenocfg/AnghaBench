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
struct TYPE_2__ {int /*<<< orphan*/  depth; } ;
struct sbitmap_queue {int round_robin; int /*<<< orphan*/ * alloc_hint; TYPE_1__ sb; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned int prandom_u32 () ; 
 int sbitmap_get (TYPE_1__*,unsigned int,int) ; 
 unsigned int this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

int __sbitmap_queue_get(struct sbitmap_queue *sbq)
{
	unsigned int hint, depth;
	int nr;

	hint = this_cpu_read(*sbq->alloc_hint);
	depth = READ_ONCE(sbq->sb.depth);
	if (unlikely(hint >= depth)) {
		hint = depth ? prandom_u32() % depth : 0;
		this_cpu_write(*sbq->alloc_hint, hint);
	}
	nr = sbitmap_get(&sbq->sb, hint, sbq->round_robin);

	if (nr == -1) {
		/* If the map is full, a hint won't do us much good. */
		this_cpu_write(*sbq->alloc_hint, 0);
	} else if (nr == hint || unlikely(sbq->round_robin)) {
		/* Only update the hint if we used it. */
		hint = nr + 1;
		if (hint >= depth - 1)
			hint = 0;
		this_cpu_write(*sbq->alloc_hint, hint);
	}

	return nr;
}