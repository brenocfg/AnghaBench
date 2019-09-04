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
struct TYPE_4__ {int start; } ;
typedef  TYPE_1__ zend_live_range ;

/* Variables and functions */

__attribute__((used)) static int cmp_live_range(const zend_live_range *a, const zend_live_range *b) {
	return a->start - b->start;
}