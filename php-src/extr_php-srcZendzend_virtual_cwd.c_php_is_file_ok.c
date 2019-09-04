#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ zend_stat_t ;
struct TYPE_6__ {int /*<<< orphan*/  cwd; } ;
typedef  TYPE_2__ cwd_state ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ php_sys_stat (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int php_is_file_ok(const cwd_state *state)  /* {{{ */
{
	zend_stat_t buf;

	if (php_sys_stat(state->cwd, &buf) == 0 && S_ISREG(buf.st_mode))
		return (0);

	return (1);
}