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
struct TYPE_2__ {int /*<<< orphan*/  (* enable_nmi ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__ arch_kgdb_ops ; 
 int /*<<< orphan*/  kgdb_nmi_console ; 
 int /*<<< orphan*/  kgdb_nmi_tty_driver ; 
 int /*<<< orphan*/  put_tty_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int tty_unregister_driver (int /*<<< orphan*/ ) ; 
 int unregister_console (int /*<<< orphan*/ *) ; 

int kgdb_unregister_nmi_console(void)
{
	int ret;

	if (!arch_kgdb_ops.enable_nmi)
		return 0;
	arch_kgdb_ops.enable_nmi(0);

	ret = unregister_console(&kgdb_nmi_console);
	if (ret)
		return ret;

	ret = tty_unregister_driver(kgdb_nmi_tty_driver);
	if (ret)
		return ret;
	put_tty_driver(kgdb_nmi_tty_driver);

	return 0;
}