#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_3__ {scalar_t__ data; } ;
typedef  TYPE_1__ RGraphNode ;
typedef  TYPE_2__ RANode ;

/* Variables and functions */

__attribute__((used)) static int first_x_cmp (const void *_a, const void *_b) {
	RGraphNode *ga = (RGraphNode *)_a;
	RGraphNode *gb = (RGraphNode *)_b;
	RANode *a = (RANode*) ga->data;
	RANode *b = (RANode*) gb->data;
	if (b->y < a->y) {
		return -1;
	}
	if (b->y > a->y) {
		return 1;
	}
	if (a->x < b->x) {
		return 1;
	}
	if (a->x > b->x) {
		return -1;
	}
	return 0;
}