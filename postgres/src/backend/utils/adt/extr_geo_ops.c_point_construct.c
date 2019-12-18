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
typedef  void* float8 ;
struct TYPE_3__ {void* y; void* x; } ;
typedef  TYPE_1__ Point ;

/* Variables and functions */

__attribute__((used)) static inline void
point_construct(Point *result, float8 x, float8 y)
{
	result->x = x;
	result->y = y;
}