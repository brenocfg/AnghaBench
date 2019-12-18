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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_4__ {scalar_t__ RegionSize; scalar_t__ BaseAddress; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RDebugMap ;
typedef  TYPE_1__ MEMORY_BASIC_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/ * add_map (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static inline RDebugMap *add_map_reg(RList *list, const char *name, MEMORY_BASIC_INFORMATION *mbi) {
	return add_map (list, name, (ut64)(size_t)mbi->BaseAddress, (ut64)mbi->RegionSize, mbi);
}