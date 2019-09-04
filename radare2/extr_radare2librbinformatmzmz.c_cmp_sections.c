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
struct TYPE_2__ {int vaddr; } ;
typedef  TYPE_1__ RBinSection ;

/* Variables and functions */

__attribute__((used)) static int cmp_sections(const void *a, const void *b) {
	const RBinSection *s_a, *s_b;

	s_a = a;
	s_b = b;

	return s_a->vaddr - s_b->vaddr;
}