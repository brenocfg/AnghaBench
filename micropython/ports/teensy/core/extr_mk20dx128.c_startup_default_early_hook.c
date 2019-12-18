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

/* Variables and functions */
 int /*<<< orphan*/  WDOG_STCTRLH ; 
 int /*<<< orphan*/  WDOG_STCTRLH_ALLOWUPDATE ; 

__attribute__((used)) static void startup_default_early_hook(void) { WDOG_STCTRLH = WDOG_STCTRLH_ALLOWUPDATE; }