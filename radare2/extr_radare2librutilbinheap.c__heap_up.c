#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ (* cmp ) (void*,void*) ;int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ RBinHeap ;

/* Variables and functions */
 void* r_pvector_at (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  r_pvector_set (int /*<<< orphan*/ *,size_t,void*) ; 
 scalar_t__ stub1 (void*,void*) ; 

__attribute__((used)) static inline void _heap_up(RBinHeap *h, size_t i, void *x) {
	size_t j;
	for (; i && (j = (i-1) >> 1, h->cmp (x, r_pvector_at (&h->a, j)) < 0); i = j) {
		r_pvector_set (&h->a, i, r_pvector_at (&h->a, j));
	}
	r_pvector_set (&h->a, i, x);
}