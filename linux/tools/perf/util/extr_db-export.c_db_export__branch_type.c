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
typedef  int /*<<< orphan*/  u32 ;
struct db_export {int (* export_branch_type ) (struct db_export*,int /*<<< orphan*/ ,char const*) ;} ;

/* Variables and functions */
 int stub1 (struct db_export*,int /*<<< orphan*/ ,char const*) ; 

int db_export__branch_type(struct db_export *dbe, u32 branch_type,
			   const char *name)
{
	if (dbe->export_branch_type)
		return dbe->export_branch_type(dbe, branch_type, name);

	return 0;
}