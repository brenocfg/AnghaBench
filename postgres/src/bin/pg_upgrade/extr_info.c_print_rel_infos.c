#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nrels; TYPE_1__* rels; } ;
struct TYPE_4__ {int /*<<< orphan*/  tablespace; int /*<<< orphan*/  reloid; int /*<<< orphan*/  relname; int /*<<< orphan*/  nspname; } ;
typedef  TYPE_2__ RelInfoArr ;

/* Variables and functions */
 int /*<<< orphan*/  PG_VERBOSE ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_rel_infos(RelInfoArr *rel_arr)
{
	int			relnum;

	for (relnum = 0; relnum < rel_arr->nrels; relnum++)
		pg_log(PG_VERBOSE, "relname: %s.%s: reloid: %u reltblspace: %s\n",
			   rel_arr->rels[relnum].nspname,
			   rel_arr->rels[relnum].relname,
			   rel_arr->rels[relnum].reloid,
			   rel_arr->rels[relnum].tablespace);
}