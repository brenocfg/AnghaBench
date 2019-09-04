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
struct TYPE_4__ {struct TYPE_4__* page_extras; struct TYPE_4__* page_starts; } ;
typedef  TYPE_1__ RDyldRebaseInfo2 ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (TYPE_1__*) ; 

__attribute__((used)) static void rebase_info2_free(RDyldRebaseInfo2 *rebase_info) {
	if (!rebase_info) {
		return;
	}

	R_FREE (rebase_info->page_starts);
	R_FREE (rebase_info->page_extras);
	R_FREE (rebase_info);
}