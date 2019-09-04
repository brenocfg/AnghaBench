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
struct TYPE_2__ {scalar_t__ off; } ;
typedef  TYPE_1__ RFlagsAtOffset ;

/* Variables and functions */

__attribute__((used)) static int flag_skiplist_cmp(const void *va, const void *vb) {
	const RFlagsAtOffset *a = (RFlagsAtOffset *)va, *b = (RFlagsAtOffset *)vb;
	if (a->off == b->off) {
		return 0;
	}
	return a->off < b->off? -1: 1;
}