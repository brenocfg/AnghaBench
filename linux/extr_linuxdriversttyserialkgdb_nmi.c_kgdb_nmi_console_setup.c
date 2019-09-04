#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct console {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* enable_nmi ) (int) ;} ;
struct TYPE_3__ {int is_console; } ;

/* Variables and functions */
 TYPE_2__ arch_kgdb_ops ; 
 TYPE_1__* dbg_io_ops ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static int kgdb_nmi_console_setup(struct console *co, char *options)
{
	arch_kgdb_ops.enable_nmi(1);

	/* The NMI console uses the dbg_io_ops to issue console messages. To
	 * avoid duplicate messages during kdb sessions we must inform kdb's
	 * I/O utilities that messages sent to the console will automatically
	 * be displayed on the dbg_io.
	 */
	dbg_io_ops->is_console = true;

	return 0;
}