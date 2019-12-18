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
struct TYPE_4__ {int /*<<< orphan*/  extraInfo; } ;
typedef  int /*<<< orphan*/  PDEBUG_HEAP_INFORMATION ;
typedef  TYPE_1__ HeapBlock ;

/* Variables and functions */
 scalar_t__ GetFirstHeapBlock (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ GetNextHeapBlock (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_return_if_fail (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_extra_info(PDEBUG_HEAP_INFORMATION heap) {
	r_return_if_fail (heap);
	HeapBlock hb;
	if (GetFirstHeapBlock (heap, &hb)) {
		do {
			R_FREE (hb.extraInfo);
		} while (GetNextHeapBlock (heap, &hb));
	}
}