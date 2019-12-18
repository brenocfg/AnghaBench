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
struct fw_unit {int dummy; } ;
struct fw_iso_resources {unsigned long long channels_mask; int allocated; int /*<<< orphan*/  mutex; struct fw_unit* unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int fw_iso_resources_init(struct fw_iso_resources *r, struct fw_unit *unit)
{
	r->channels_mask = ~0uLL;
	r->unit = unit;
	mutex_init(&r->mutex);
	r->allocated = false;

	return 0;
}