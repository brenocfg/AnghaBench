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
struct map_event_t {int id; } ;

/* Variables and functions */

__attribute__((used)) static int _cmp_map_event_by_id(const void *a_, const void *b_) {
	struct map_event_t *a = (void *)a_, *b = (void *)b_;
	return a->id - b->id;
}