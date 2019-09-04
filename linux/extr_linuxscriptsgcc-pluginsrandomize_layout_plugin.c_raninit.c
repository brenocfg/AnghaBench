#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct TYPE_4__ {void* d; void* c; void* b; void* a; } ;
typedef  TYPE_1__ ranctx ;

/* Variables and functions */
 int /*<<< orphan*/  ranval (TYPE_1__*) ; 

__attribute__((used)) static void raninit(ranctx *x, u64 *seed) {
	int i;

	x->a = seed[0];
	x->b = seed[1];
	x->c = seed[2];
	x->d = seed[3];

	for (i=0; i < 30; ++i)
		(void)ranval(x);
}