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
struct btf_dedup {int hypot_cnt; size_t* hypot_list; int /*<<< orphan*/ * hypot_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_UNPROCESSED_ID ; 

__attribute__((used)) static void btf_dedup_clear_hypot_map(struct btf_dedup *d)
{
	int i;

	for (i = 0; i < d->hypot_cnt; i++)
		d->hypot_map[d->hypot_list[i]] = BTF_UNPROCESSED_ID;
	d->hypot_cnt = 0;
}