#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int initialized; int /*<<< orphan*/ * bt_stop_list; int /*<<< orphan*/ * comm_list; int /*<<< orphan*/ * dso_list; int /*<<< orphan*/ * sym_list; int /*<<< orphan*/  pid_list; int /*<<< orphan*/  tid_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  intlist__delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlist__delete (int /*<<< orphan*/ *) ; 
 TYPE_1__ symbol_conf ; 
 int /*<<< orphan*/  vmlinux_path__exit () ; 

void symbol__exit(void)
{
	if (!symbol_conf.initialized)
		return;
	strlist__delete(symbol_conf.bt_stop_list);
	strlist__delete(symbol_conf.sym_list);
	strlist__delete(symbol_conf.dso_list);
	strlist__delete(symbol_conf.comm_list);
	intlist__delete(symbol_conf.tid_list);
	intlist__delete(symbol_conf.pid_list);
	vmlinux_path__exit();
	symbol_conf.sym_list = symbol_conf.dso_list = symbol_conf.comm_list = NULL;
	symbol_conf.bt_stop_list = NULL;
	symbol_conf.initialized = false;
}