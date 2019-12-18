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
struct TYPE_4__ {size_t size; scalar_t__ (* f_eq ) (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ gbtree_ninfo ;
struct TYPE_5__ {int /*<<< orphan*/  const* upper; int /*<<< orphan*/  const* lower; } ;
typedef  TYPE_2__ GBT_NUMKEY_R ;
typedef  int /*<<< orphan*/  GBT_NUMKEY ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

bool
gbt_num_same(const GBT_NUMKEY *a, const GBT_NUMKEY *b, const gbtree_ninfo *tinfo, FmgrInfo *flinfo)
{
	GBT_NUMKEY_R b1,
				b2;

	b1.lower = &(a[0]);
	b1.upper = &(a[tinfo->size]);
	b2.lower = &(b[0]);
	b2.upper = &(b[tinfo->size]);

	return (tinfo->f_eq(b1.lower, b2.lower, flinfo) &&
			tinfo->f_eq(b1.upper, b2.upper, flinfo));
}