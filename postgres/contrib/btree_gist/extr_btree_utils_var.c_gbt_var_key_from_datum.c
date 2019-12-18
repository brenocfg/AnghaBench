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
struct varlena {int dummy; } ;
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  GBT_VARKEY ;

/* Variables and functions */
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  VARDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 scalar_t__ VARSIZE (struct varlena const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct varlena const*,scalar_t__) ; 
 scalar_t__ palloc (scalar_t__) ; 

__attribute__((used)) static GBT_VARKEY *
gbt_var_key_from_datum(const struct varlena *u)
{
	int32		lowersize = VARSIZE(u);
	GBT_VARKEY *r;

	r = (GBT_VARKEY *) palloc(lowersize + VARHDRSZ);
	memcpy(VARDATA(r), u, lowersize);
	SET_VARSIZE(r, lowersize + VARHDRSZ);

	return r;
}