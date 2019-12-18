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
typedef  int /*<<< orphan*/  u64 ;
struct db_export {int dummy; } ;
struct call_return {int dummy; } ;

/* Variables and functions */
 int db_export__call_return (struct db_export*,struct call_return*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int python_process_call_return(struct call_return *cr, u64 *parent_db_id,
				      void *data)
{
	struct db_export *dbe = data;

	return db_export__call_return(dbe, cr, parent_db_id);
}