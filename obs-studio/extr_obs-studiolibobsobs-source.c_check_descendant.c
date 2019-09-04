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
struct descendant_info {int exists; int /*<<< orphan*/ * target; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */

__attribute__((used)) static void check_descendant(obs_source_t *parent, obs_source_t *child,
		void *param)
{
	struct descendant_info *info = param;
	if (child == info->target || parent == info->target)
		info->exists = true;
}