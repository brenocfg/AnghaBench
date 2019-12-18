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
struct TYPE_2__ {int bandwidth_overhead; } ;
struct cmp_connection {TYPE_1__ resources; } ;

/* Variables and functions */

__attribute__((used)) static int get_overhead_id(struct cmp_connection *c)
{
	int id;

	/*
	 * apply "oPCR overhead ID encoding"
	 * the encoding table can convert up to 512.
	 * here the value over 512 is converted as the same way as 512.
	 */
	for (id = 1; id < 16; id++) {
		if (c->resources.bandwidth_overhead < (id << 5))
			break;
	}
	if (id == 16)
		id = 0;

	return id;
}