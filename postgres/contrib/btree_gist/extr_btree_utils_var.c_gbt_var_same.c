#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ (* f_cmp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ gbtree_vinfo ;
struct TYPE_6__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ GBT_VARKEY_R ;
typedef  int /*<<< orphan*/  GBT_VARKEY ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 TYPE_2__ gbt_var_key_readable (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool
gbt_var_same(Datum d1, Datum d2, Oid collation,
			 const gbtree_vinfo *tinfo, FmgrInfo *flinfo)
{
	GBT_VARKEY *t1 = (GBT_VARKEY *) DatumGetPointer(d1);
	GBT_VARKEY *t2 = (GBT_VARKEY *) DatumGetPointer(d2);
	GBT_VARKEY_R r1,
				r2;

	r1 = gbt_var_key_readable(t1);
	r2 = gbt_var_key_readable(t2);

	return (tinfo->f_cmp(r1.lower, r2.lower, collation, flinfo) == 0 &&
			tinfo->f_cmp(r1.upper, r2.upper, collation, flinfo) == 0);
}