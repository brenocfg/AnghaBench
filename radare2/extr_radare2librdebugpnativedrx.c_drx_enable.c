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
typedef  int /*<<< orphan*/  drxt ;

/* Variables and functions */
 size_t DR_CONTROL ; 
 int /*<<< orphan*/  I386_DR_DISABLE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I386_DR_ENABLE (int /*<<< orphan*/ ,int) ; 

void drx_enable(drxt *r, int n, int enabled) {
	if (enabled) {
		I386_DR_ENABLE (r[DR_CONTROL], n);
	} else {
		I386_DR_DISABLE (r[DR_CONTROL], n);
	}
}