#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* y; void* x; } ;
struct TYPE_8__ {void* y; void* x; } ;
struct TYPE_9__ {TYPE_1__ low; TYPE_2__ high; } ;
typedef  TYPE_3__ BOX ;

/* Variables and functions */
 void* float8_max (void*,void*) ; 
 void* float8_min (void*,void*) ; 

__attribute__((used)) static void
rt_box_union(BOX *n, const BOX *a, const BOX *b)
{
	n->high.x = float8_max(a->high.x, b->high.x);
	n->high.y = float8_max(a->high.y, b->high.y);
	n->low.x = float8_min(a->low.x, b->low.x);
	n->low.y = float8_min(a->low.y, b->low.y);
}