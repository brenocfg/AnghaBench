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
 int /*<<< orphan*/  ACCESS_WATCHPOINT ; 
 int set_bp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int) ; 

int gdbr_set_hwa(libgdbr_t *g, ut64 address, const char *conditions, int sizebp) {
	return set_bp (g, address, conditions, ACCESS_WATCHPOINT, sizebp);
}