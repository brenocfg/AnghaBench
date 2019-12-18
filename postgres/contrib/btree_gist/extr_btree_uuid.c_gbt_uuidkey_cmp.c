#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
typedef  TYPE_1__ uuidKEY ;
struct TYPE_4__ {scalar_t__ t; } ;
typedef  TYPE_2__ Nsrt ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
 int uuid_internal_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gbt_uuidkey_cmp(const void *a, const void *b, FmgrInfo *flinfo)
{
	uuidKEY    *ia = (uuidKEY *) (((const Nsrt *) a)->t);
	uuidKEY    *ib = (uuidKEY *) (((const Nsrt *) b)->t);
	int			res;

	res = uuid_internal_cmp(&ia->lower, &ib->lower);
	if (res == 0)
		res = uuid_internal_cmp(&ia->upper, &ib->upper);
	return res;
}