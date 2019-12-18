#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TocEntry ;
struct TYPE_3__ {size_t last_te; int sorted; int /*<<< orphan*/ ** tes; } ;
typedef  TYPE_1__ ParallelReadyList ;

/* Variables and functions */

__attribute__((used)) static void
ready_list_insert(ParallelReadyList *ready_list, TocEntry *te)
{
	ready_list->tes[++ready_list->last_te] = te;
	/* List is (probably) not sorted anymore. */
	ready_list->sorted = false;
}