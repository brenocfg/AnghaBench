#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int (* f_ge ) (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int (* f_gt ) (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int (* f_eq ) (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int (* f_lt ) (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int (* f_le ) (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* f_cmp ) (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ gbtree_vinfo ;
struct TYPE_8__ {void const* lower; void const* upper; } ;
typedef  int StrategyNumber ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ GBT_VARKEY_R ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
#define  BTEqualStrategyNumber 133 
#define  BTGreaterEqualStrategyNumber 132 
#define  BTGreaterStrategyNumber 131 
#define  BTLessEqualStrategyNumber 130 
#define  BTLessStrategyNumber 129 
#define  BtreeGistNotEqualStrategyNumber 128 
 int /*<<< orphan*/  gbt_var_node_pf_match (TYPE_2__*,void const*,TYPE_1__ const*) ; 
 int stub1 (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub10 (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub11 (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub12 (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub13 (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub3 (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub5 (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub8 (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool
gbt_var_consistent(GBT_VARKEY_R *key,
				   const void *query,
				   StrategyNumber strategy,
				   Oid collation,
				   bool is_leaf,
				   const gbtree_vinfo *tinfo,
				   FmgrInfo *flinfo)
{
	bool		retval = false;

	switch (strategy)
	{
		case BTLessEqualStrategyNumber:
			if (is_leaf)
				retval = tinfo->f_ge(query, key->lower, collation, flinfo);
			else
				retval = tinfo->f_cmp(query, key->lower, collation, flinfo) >= 0
					|| gbt_var_node_pf_match(key, query, tinfo);
			break;
		case BTLessStrategyNumber:
			if (is_leaf)
				retval = tinfo->f_gt(query, key->lower, collation, flinfo);
			else
				retval = tinfo->f_cmp(query, key->lower, collation, flinfo) >= 0
					|| gbt_var_node_pf_match(key, query, tinfo);
			break;
		case BTEqualStrategyNumber:
			if (is_leaf)
				retval = tinfo->f_eq(query, key->lower, collation, flinfo);
			else
				retval =
					(tinfo->f_cmp(key->lower, query, collation, flinfo) <= 0 &&
					 tinfo->f_cmp(query, key->upper, collation, flinfo) <= 0) ||
					gbt_var_node_pf_match(key, query, tinfo);
			break;
		case BTGreaterStrategyNumber:
			if (is_leaf)
				retval = tinfo->f_lt(query, key->upper, collation, flinfo);
			else
				retval = tinfo->f_cmp(query, key->upper, collation, flinfo) <= 0
					|| gbt_var_node_pf_match(key, query, tinfo);
			break;
		case BTGreaterEqualStrategyNumber:
			if (is_leaf)
				retval = tinfo->f_le(query, key->upper, collation, flinfo);
			else
				retval = tinfo->f_cmp(query, key->upper, collation, flinfo) <= 0
					|| gbt_var_node_pf_match(key, query, tinfo);
			break;
		case BtreeGistNotEqualStrategyNumber:
			retval = !(tinfo->f_eq(query, key->lower, collation, flinfo) &&
					   tinfo->f_eq(query, key->upper, collation, flinfo));
			break;
		default:
			retval = false;
	}

	return retval;
}