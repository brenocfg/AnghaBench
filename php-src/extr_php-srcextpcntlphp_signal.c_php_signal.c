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
typedef  int /*<<< orphan*/  Sigfunc ;

/* Variables and functions */
 int /*<<< orphan*/ * php_signal4 (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

Sigfunc *php_signal(int signo, Sigfunc *func, int restart)
{
	return php_signal4(signo, func, restart, 0);
}