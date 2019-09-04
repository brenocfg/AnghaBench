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
 int /*<<< orphan*/  FPM_CLEANUP_PARENT ; 
 scalar_t__ fpm_cleanup_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_php_cleanup ; 

int fpm_php_init_main() /* {{{ */
{
	if (0 > fpm_cleanup_add(FPM_CLEANUP_PARENT, fpm_php_cleanup, 0)) {
		return -1;
	}
	return 0;
}