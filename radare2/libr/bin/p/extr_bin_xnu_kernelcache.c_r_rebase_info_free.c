#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* ranges; } ;
typedef  TYPE_1__ RRebaseInfo ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (TYPE_1__*) ; 

__attribute__((used)) static void r_rebase_info_free(RRebaseInfo *info) {
	if (!info) {
		return;
	}

	if (info->ranges) {
		R_FREE (info->ranges);
		info->ranges = NULL;
	}

	R_FREE (info);
}