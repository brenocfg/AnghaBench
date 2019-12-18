#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* diff; } ;
struct TYPE_5__ {scalar_t__ dist; } ;
typedef  TYPE_2__ RAnalFunction ;

/* Variables and functions */

__attribute__((used)) static int compareDist(const RAnalFunction *a, const RAnalFunction *b) {
	return a && b && a->diff->dist && b->diff->dist && a->diff->dist > b->diff->dist;
}