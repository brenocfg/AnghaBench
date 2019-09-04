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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ phpdbg_watchpoint_t ;

/* Variables and functions */
 int /*<<< orphan*/  WATCH_ON_ZVAL ; 
 int /*<<< orphan*/  phpdbg_set_addr_watchpoint (int /*<<< orphan*/ *,int,TYPE_1__*) ; 

void phpdbg_set_zval_watchpoint(zval *zv, phpdbg_watchpoint_t *watch) {
	phpdbg_set_addr_watchpoint(zv, sizeof(zval) - sizeof(uint32_t), watch);
	watch->type = WATCH_ON_ZVAL;
}