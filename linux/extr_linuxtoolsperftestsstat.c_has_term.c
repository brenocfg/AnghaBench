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
typedef  scalar_t__ u64 ;
struct stat_config_event {unsigned int nr; TYPE_1__* data; } ;
struct TYPE_2__ {scalar_t__ tag; scalar_t__ val; } ;

/* Variables and functions */

__attribute__((used)) static bool has_term(struct stat_config_event *config,
		     u64 tag, u64 val)
{
	unsigned i;

	for (i = 0; i < config->nr; i++) {
		if ((config->data[i].tag == tag) &&
		    (config->data[i].val == val))
			return true;
	}

	return false;
}