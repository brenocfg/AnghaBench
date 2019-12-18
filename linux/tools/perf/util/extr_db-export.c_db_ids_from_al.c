#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct dso {scalar_t__ db_id; } ;
struct db_export {int dummy; } ;
struct addr_location {TYPE_2__* sym; scalar_t__ addr; int /*<<< orphan*/  machine; TYPE_1__* map; } ;
struct TYPE_7__ {scalar_t__ start; } ;
struct TYPE_6__ {struct dso* dso; } ;

/* Variables and functions */
 int db_export__dso (struct db_export*,struct dso*,int /*<<< orphan*/ ) ; 
 int db_export__symbol (struct db_export*,TYPE_2__*,struct dso*) ; 
 int /*<<< orphan*/  dso__insert_symbol (struct dso*,TYPE_2__*) ; 
 TYPE_2__* symbol__new (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__* symbol__priv (TYPE_2__*) ; 

__attribute__((used)) static int db_ids_from_al(struct db_export *dbe, struct addr_location *al,
			  u64 *dso_db_id, u64 *sym_db_id, u64 *offset)
{
	int err;

	if (al->map) {
		struct dso *dso = al->map->dso;

		err = db_export__dso(dbe, dso, al->machine);
		if (err)
			return err;
		*dso_db_id = dso->db_id;

		if (!al->sym) {
			al->sym = symbol__new(al->addr, 0, 0, 0, "unknown");
			if (al->sym)
				dso__insert_symbol(dso, al->sym);
		}

		if (al->sym) {
			u64 *db_id = symbol__priv(al->sym);

			err = db_export__symbol(dbe, al->sym, dso);
			if (err)
				return err;
			*sym_db_id = *db_id;
			*offset = al->addr - al->sym->start;
		}
	}

	return 0;
}