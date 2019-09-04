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
struct machine {scalar_t__ db_id; } ;
struct db_export {int (* export_machine ) (struct db_export*,struct machine*) ;scalar_t__ machine_last_db_id; } ;

/* Variables and functions */
 int stub1 (struct db_export*,struct machine*) ; 

int db_export__machine(struct db_export *dbe, struct machine *machine)
{
	if (machine->db_id)
		return 0;

	machine->db_id = ++dbe->machine_last_db_id;

	if (dbe->export_machine)
		return dbe->export_machine(dbe, machine);

	return 0;
}