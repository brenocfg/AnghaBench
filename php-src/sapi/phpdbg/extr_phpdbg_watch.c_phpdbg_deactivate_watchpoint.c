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
typedef  int /*<<< orphan*/  phpdbg_watchpoint_t ;

/* Variables and functions */
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  phpdbg_change_watchpoint_access (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void phpdbg_deactivate_watchpoint(phpdbg_watchpoint_t *watch) {
	phpdbg_change_watchpoint_access(watch, PROT_READ | PROT_WRITE);
}