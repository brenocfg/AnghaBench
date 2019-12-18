#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  threads; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ RListIter ;
typedef  int /*<<< orphan*/  RListComparator ;
typedef  TYPE_2__ RDebug ;
typedef  int /*<<< orphan*/ * PTHREAD_ITEM ;

/* Variables and functions */
 scalar_t__ __w32_findthread_cmp ; 
 TYPE_1__* r_list_find (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline PTHREAD_ITEM __find_thread(RDebug *dbg, int tid) {
	RListIter *it = r_list_find (dbg->threads, &tid, (RListComparator)__w32_findthread_cmp);
	return it ? it->data : NULL;
}