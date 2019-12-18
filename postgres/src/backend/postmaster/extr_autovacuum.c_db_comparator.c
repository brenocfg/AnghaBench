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
struct TYPE_2__ {scalar_t__ adl_score; } ;
typedef  TYPE_1__ avl_dbase ;

/* Variables and functions */

__attribute__((used)) static int
db_comparator(const void *a, const void *b)
{
	if (((const avl_dbase *) a)->adl_score == ((const avl_dbase *) b)->adl_score)
		return 0;
	else
		return (((const avl_dbase *) a)->adl_score < ((const avl_dbase *) b)->adl_score) ? 1 : -1;
}