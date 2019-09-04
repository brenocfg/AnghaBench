#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  log_source; int /*<<< orphan*/  mail_socket; } ;
typedef  TYPE_1__ php_win32_core_globals ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  INVALID_SOCKET ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void php_win32_core_globals_ctor(void *vg)
{/*{{{*/
	php_win32_core_globals *wg = (php_win32_core_globals*)vg;
	memset(wg, 0, sizeof(*wg));

	wg->mail_socket = INVALID_SOCKET;

	wg->log_source = INVALID_HANDLE_VALUE;
}