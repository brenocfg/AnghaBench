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
 int /*<<< orphan*/  checkEdge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delInvalidPanels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixBlockSize (TYPE_1__*) ; 
 int /*<<< orphan*/  panels_check_stackbase (TYPE_1__*) ; 
 int /*<<< orphan*/  panels_refresh (TYPE_1__*) ; 

__attribute__((used)) static void panels_layout_refresh(RCore *core) {
	fixBlockSize (core);
	delInvalidPanels (core->panels);
	checkEdge (core->panels);
	panels_check_stackbase (core);
	panels_refresh (core);
}