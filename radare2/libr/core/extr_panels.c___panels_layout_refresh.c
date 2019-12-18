#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  panels; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __check_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __del_invalid_panels (TYPE_1__*) ; 
 int /*<<< orphan*/  __panels_check_stackbase (TYPE_1__*) ; 
 int /*<<< orphan*/  __panels_refresh (TYPE_1__*) ; 

void __panels_layout_refresh(RCore *core) {
	__del_invalid_panels (core);
	__check_edge (core->panels);
	__panels_check_stackbase (core);
	__panels_refresh (core);
}