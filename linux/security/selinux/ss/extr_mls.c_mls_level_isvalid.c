#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  nprim; } ;
struct TYPE_6__ {scalar_t__ nprim; int /*<<< orphan*/  table; } ;
struct policydb {TYPE_2__ p_cats; TYPE_3__ p_levels; } ;
struct mls_level {scalar_t__ sens; int /*<<< orphan*/  cat; } ;
struct level_datum {TYPE_1__* level; } ;
struct TYPE_4__ {int /*<<< orphan*/  cat; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYM_LEVELS ; 
 int ebitmap_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct level_datum* hashtab_search (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_name (struct policydb*,int /*<<< orphan*/ ,scalar_t__) ; 

int mls_level_isvalid(struct policydb *p, struct mls_level *l)
{
	struct level_datum *levdatum;

	if (!l->sens || l->sens > p->p_levels.nprim)
		return 0;
	levdatum = hashtab_search(p->p_levels.table,
				  sym_name(p, SYM_LEVELS, l->sens - 1));
	if (!levdatum)
		return 0;

	/*
	 * Return 1 iff all the bits set in l->cat are also be set in
	 * levdatum->level->cat and no bit in l->cat is larger than
	 * p->p_cats.nprim.
	 */
	return ebitmap_contains(&levdatum->level->cat, &l->cat,
				p->p_cats.nprim);
}