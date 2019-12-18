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
typedef  scalar_t__ u64 ;
struct symbol {int dummy; } ;
struct dso {int dummy; } ;
struct db_export {int (* export_symbol ) (struct db_export*,struct symbol*,struct dso*) ;scalar_t__ symbol_last_db_id; } ;

/* Variables and functions */
 int stub1 (struct db_export*,struct symbol*,struct dso*) ; 
 scalar_t__* symbol__priv (struct symbol*) ; 

int db_export__symbol(struct db_export *dbe, struct symbol *sym,
		      struct dso *dso)
{
	u64 *sym_db_id = symbol__priv(sym);

	if (*sym_db_id)
		return 0;

	*sym_db_id = ++dbe->symbol_last_db_id;

	if (dbe->export_symbol)
		return dbe->export_symbol(dbe, sym, dso);

	return 0;
}