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
struct TYPE_3__ {int y; int x; } ;
typedef  TYPE_1__ RANode ;

/* Variables and functions */

__attribute__((used)) static int is_near(const RANode *n, int x, int y, int is_next) {
	if (is_next) {
		return (n->y == y && n->x > x) || n->y > y;
	}
	return (n->y == y && n->x < x) || n->y < y;
}