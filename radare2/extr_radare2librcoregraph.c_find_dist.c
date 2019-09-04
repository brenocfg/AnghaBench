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
struct dist_t {scalar_t__ from; scalar_t__ to; } ;

/* Variables and functions */

__attribute__((used)) static int find_dist(const struct dist_t *a, const struct dist_t *b) {
	return a->from == b->from && a->to == b->to? 0: 1;
}