#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  flinfo; int /*<<< orphan*/  collation; TYPE_1__* tinfo; } ;
typedef  TYPE_2__ gbt_vsrt_arg ;
struct TYPE_8__ {int /*<<< orphan*/  t; } ;
typedef  TYPE_3__ Vsrt ;
struct TYPE_9__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_6__ {int (* f_cmp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ GBT_VARKEY_R ;

/* Variables and functions */
 TYPE_4__ gbt_var_key_readable (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gbt_vsrt_cmp(const void *a, const void *b, void *arg)
{
	GBT_VARKEY_R ar = gbt_var_key_readable(((const Vsrt *) a)->t);
	GBT_VARKEY_R br = gbt_var_key_readable(((const Vsrt *) b)->t);
	const gbt_vsrt_arg *varg = (const gbt_vsrt_arg *) arg;
	int			res;

	res = varg->tinfo->f_cmp(ar.lower, br.lower, varg->collation, varg->flinfo);
	if (res == 0)
		return varg->tinfo->f_cmp(ar.upper, br.upper, varg->collation, varg->flinfo);

	return res;
}