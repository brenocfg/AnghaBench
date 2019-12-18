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
struct machine {int dummy; } ;
struct dso {scalar_t__ db_id; } ;
struct db_export {int (* export_dso ) (struct db_export*,struct dso*,struct machine*) ;scalar_t__ dso_last_db_id; } ;

/* Variables and functions */
 int stub1 (struct db_export*,struct dso*,struct machine*) ; 

int db_export__dso(struct db_export *dbe, struct dso *dso,
		   struct machine *machine)
{
	if (dso->db_id)
		return 0;

	dso->db_id = ++dbe->dso_last_db_id;

	if (dbe->export_dso)
		return dbe->export_dso(dbe, dso, machine);

	return 0;
}