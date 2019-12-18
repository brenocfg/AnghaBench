#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_3__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
typedef  TYPE_1__ GBT_VARKEY_R ;
typedef  int /*<<< orphan*/  GBT_VARKEY ;

/* Variables and functions */
 scalar_t__ INTALIGN (scalar_t__) ; 
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ VARDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 scalar_t__ VARSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ palloc0 (scalar_t__) ; 

GBT_VARKEY *
gbt_var_key_copy(const GBT_VARKEY_R *u)
{
	int32		lowersize = VARSIZE(u->lower);
	int32		uppersize = VARSIZE(u->upper);
	GBT_VARKEY *r;

	r = (GBT_VARKEY *) palloc0(INTALIGN(lowersize) + uppersize + VARHDRSZ);
	memcpy(VARDATA(r), u->lower, lowersize);
	memcpy(VARDATA(r) + INTALIGN(lowersize), u->upper, uppersize);
	SET_VARSIZE(r, INTALIGN(lowersize) + uppersize + VARHDRSZ);

	return r;
}