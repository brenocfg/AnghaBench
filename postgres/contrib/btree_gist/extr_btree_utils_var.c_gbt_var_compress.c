#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct varlena {int dummy; } ;
typedef  int /*<<< orphan*/  gbtree_vinfo ;
struct TYPE_6__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  page; int /*<<< orphan*/  rel; int /*<<< orphan*/  key; scalar_t__ leafkey; } ;
typedef  TYPE_1__ GISTENTRY ;
typedef  int /*<<< orphan*/  GBT_VARKEY ;

/* Variables and functions */
 struct varlena* PG_DETOAST_DATUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gbt_var_key_from_datum (struct varlena*) ; 
 int /*<<< orphan*/  gistentryinit (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* palloc (int) ; 

GISTENTRY *
gbt_var_compress(GISTENTRY *entry, const gbtree_vinfo *tinfo)
{
	GISTENTRY  *retval;

	if (entry->leafkey)
	{
		struct varlena *leaf = PG_DETOAST_DATUM(entry->key);
		GBT_VARKEY *r;

		r = gbt_var_key_from_datum(leaf);

		retval = palloc(sizeof(GISTENTRY));
		gistentryinit(*retval, PointerGetDatum(r),
					  entry->rel, entry->page,
					  entry->offset, true);
	}
	else
		retval = entry;

	return retval;
}