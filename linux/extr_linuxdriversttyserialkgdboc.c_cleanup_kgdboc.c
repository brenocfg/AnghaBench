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
 int configured ; 
 int /*<<< orphan*/  kgdb_unregister_io_module (int /*<<< orphan*/ *) ; 
 scalar_t__ kgdb_unregister_nmi_console () ; 
 int /*<<< orphan*/  kgdboc_io_ops ; 
 int /*<<< orphan*/  kgdboc_unregister_kbd () ; 

__attribute__((used)) static void cleanup_kgdboc(void)
{
	if (kgdb_unregister_nmi_console())
		return;
	kgdboc_unregister_kbd();
	if (configured == 1)
		kgdb_unregister_io_module(&kgdboc_io_ops);
}