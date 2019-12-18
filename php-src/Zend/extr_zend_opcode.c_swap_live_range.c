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
struct TYPE_4__ {void* end; void* start; void* var; } ;
typedef  TYPE_1__ zend_live_range ;
typedef  void* uint32_t ;

/* Variables and functions */

__attribute__((used)) static void swap_live_range(zend_live_range *a, zend_live_range *b) {
	uint32_t tmp;
	tmp = a->var;
	a->var = b->var;
	b->var = tmp;
	tmp = a->start;
	a->start = b->start;
	b->start = tmp;
	tmp = a->end;
	a->end = b->end;
	b->end = tmp;
}