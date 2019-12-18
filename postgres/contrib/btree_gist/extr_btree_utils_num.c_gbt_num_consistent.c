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
struct TYPE_5__ {int (* f_ge ) (void const*,void const*,int /*<<< orphan*/ *) ;int (* f_gt ) (void const*,void const*,int /*<<< orphan*/ *) ;int (* f_eq ) (void const*,void const*,int /*<<< orphan*/ *) ;int (* f_le ) (void const*,void const*,int /*<<< orphan*/ *) ;int (* f_lt ) (void const*,void const*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ gbtree_ninfo ;
struct TYPE_6__ {void const* lower; void const* upper; } ;
typedef  int StrategyNumber ;
typedef  TYPE_2__ GBT_NUMKEY_R ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
#define  BTEqualStrategyNumber 133 
#define  BTGreaterEqualStrategyNumber 132 
#define  BTGreaterStrategyNumber 131 
#define  BTLessEqualStrategyNumber 130 
#define  BTLessStrategyNumber 129 
#define  BtreeGistNotEqualStrategyNumber 128 
 int stub1 (void const*,void const*,int /*<<< orphan*/ *) ; 
 int stub10 (void const*,void const*,int /*<<< orphan*/ *) ; 
 int stub11 (void const*,void const*,int /*<<< orphan*/ *) ; 
 int stub2 (void const*,void const*,int /*<<< orphan*/ *) ; 
 int stub3 (void const*,void const*,int /*<<< orphan*/ *) ; 
 int stub4 (void const*,void const*,int /*<<< orphan*/ *) ; 
 int stub5 (void const*,void const*,int /*<<< orphan*/ *) ; 
 int stub6 (void const*,void const*,int /*<<< orphan*/ *) ; 
 int stub7 (void const*,void const*,int /*<<< orphan*/ *) ; 
 int stub8 (void const*,void const*,int /*<<< orphan*/ *) ; 
 int stub9 (void const*,void const*,int /*<<< orphan*/ *) ; 

bool
gbt_num_consistent(const GBT_NUMKEY_R *key,
				   const void *query,
				   const StrategyNumber *strategy,
				   bool is_leaf,
				   const gbtree_ninfo *tinfo,
				   FmgrInfo *flinfo)
{
	bool		retval;

	switch (*strategy)
	{
		case BTLessEqualStrategyNumber:
			retval = tinfo->f_ge(query, key->lower, flinfo);
			break;
		case BTLessStrategyNumber:
			if (is_leaf)
				retval = tinfo->f_gt(query, key->lower, flinfo);
			else
				retval = tinfo->f_ge(query, key->lower, flinfo);
			break;
		case BTEqualStrategyNumber:
			if (is_leaf)
				retval = tinfo->f_eq(query, key->lower, flinfo);
			else
				retval = (tinfo->f_le(key->lower, query, flinfo) &&
						  tinfo->f_le(query, key->upper, flinfo));
			break;
		case BTGreaterStrategyNumber:
			if (is_leaf)
				retval = tinfo->f_lt(query, key->upper, flinfo);
			else
				retval = tinfo->f_le(query, key->upper, flinfo);
			break;
		case BTGreaterEqualStrategyNumber:
			retval = tinfo->f_le(query, key->upper, flinfo);
			break;
		case BtreeGistNotEqualStrategyNumber:
			retval = (!(tinfo->f_eq(query, key->lower, flinfo) &&
						tinfo->f_eq(query, key->upper, flinfo)));
			break;
		default:
			retval = false;
	}

	return retval;
}