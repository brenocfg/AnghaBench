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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  libgdbr_t ;

/* Variables and functions */
 int /*<<< orphan*/  HARDWARE_BREAKPOINT ; 
 int remove_bp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int gdbr_remove_hwbp(libgdbr_t *g, ut64 address, int sizebp) {
	return remove_bp (g, address, HARDWARE_BREAKPOINT, sizebp);
}