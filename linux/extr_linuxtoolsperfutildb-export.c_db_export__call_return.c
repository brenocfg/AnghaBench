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
struct db_export {int (* export_call_return ) (struct db_export*,struct call_return*) ;scalar_t__ call_return_last_db_id; } ;
struct call_return {scalar_t__ db_id; int /*<<< orphan*/  cp; } ;

/* Variables and functions */
 int db_export__call_path (struct db_export*,int /*<<< orphan*/ ) ; 
 int stub1 (struct db_export*,struct call_return*) ; 

int db_export__call_return(struct db_export *dbe, struct call_return *cr)
{
	int err;

	if (cr->db_id)
		return 0;

	err = db_export__call_path(dbe, cr->cp);
	if (err)
		return err;

	cr->db_id = ++dbe->call_return_last_db_id;

	if (dbe->export_call_return)
		return dbe->export_call_return(dbe, cr);

	return 0;
}