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
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 scalar_t__ IS_MODE_JSON (int) ; 
 int /*<<< orphan*/  r_cons_printf (char*) ; 

__attribute__((used)) static void bin_no_resources(RCore *r, int mode) {
	if (IS_MODE_JSON (mode)) {
		r_cons_printf ("[]");
	}
}