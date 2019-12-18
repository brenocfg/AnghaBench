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
struct crush_choose_arg {int /*<<< orphan*/ * ids; } ;
struct TYPE_2__ {int /*<<< orphan*/ * items; } ;
struct crush_bucket_straw2 {TYPE_1__ h; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */

__attribute__((used)) static __s32 *get_choose_arg_ids(const struct crush_bucket_straw2 *bucket,
				 const struct crush_choose_arg *arg)
{
	if (!arg || !arg->ids)
		return bucket->h.items;

	return arg->ids;
}