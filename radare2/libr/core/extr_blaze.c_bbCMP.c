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
struct TYPE_2__ {int start; } ;
typedef  TYPE_1__ bb_t ;

/* Variables and functions */

__attribute__((used)) static int bbCMP (void *_a, void *_b) {
	bb_t *a = (bb_t*)_a;
	bb_t *b = (bb_t*)_b;
	return b->start - a->start;
}