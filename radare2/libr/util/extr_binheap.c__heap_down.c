#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t len; } ;
struct TYPE_8__ {TYPE_1__ v; } ;
struct TYPE_7__ {scalar_t__ (* cmp ) (void*,void*) ;TYPE_3__ a; } ;
typedef  TYPE_2__ RBinHeap ;

/* Variables and functions */
 void* r_pvector_at (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  r_pvector_set (TYPE_3__*,size_t,void*) ; 
 scalar_t__ stub1 (void*,void*) ; 
 scalar_t__ stub2 (void*,void*) ; 

__attribute__((used)) static inline void _heap_down(RBinHeap *h, size_t i, void *x) {
	size_t j;
	for (; j = i * 2 + 1, j < h->a.v.len; i = j) {
		if (j + 1 < h->a.v.len && h->cmp (r_pvector_at (&h->a, j+1), r_pvector_at (&h->a, j)) < 0) {
			j++;
		}
		if (h->cmp (r_pvector_at (&h->a, j), x) >= 0) {
			break;
		}
		r_pvector_set (&h->a, i, r_pvector_at (&h->a, j));
	}
	r_pvector_set (&h->a, i, x);
}