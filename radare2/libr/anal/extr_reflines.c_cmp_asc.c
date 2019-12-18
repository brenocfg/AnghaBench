#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct refline_end {scalar_t__ val; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_asc(const struct refline_end *a, const struct refline_end *b) {
	return a->val > b->val;
}