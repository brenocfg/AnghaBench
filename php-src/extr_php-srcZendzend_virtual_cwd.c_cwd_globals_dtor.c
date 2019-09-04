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
typedef  int /*<<< orphan*/  virtual_cwd_globals ;

/* Variables and functions */
 int /*<<< orphan*/  realpath_cache_clean () ; 

__attribute__((used)) static void cwd_globals_dtor(virtual_cwd_globals *cwd_g) /* {{{ */
{
	realpath_cache_clean();
}