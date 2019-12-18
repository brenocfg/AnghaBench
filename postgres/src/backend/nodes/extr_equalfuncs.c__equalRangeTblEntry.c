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
typedef  int /*<<< orphan*/  RangeTblEntry ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alias ; 
 int /*<<< orphan*/  checkAsUser ; 
 int /*<<< orphan*/  colcollations ; 
 int /*<<< orphan*/  coltypes ; 
 int /*<<< orphan*/  coltypmods ; 
 int /*<<< orphan*/  ctelevelsup ; 
 int /*<<< orphan*/  ctename ; 
 int /*<<< orphan*/  enrname ; 
 int /*<<< orphan*/  enrtuples ; 
 int /*<<< orphan*/  eref ; 
 int /*<<< orphan*/  extraUpdatedCols ; 
 int /*<<< orphan*/  funcordinality ; 
 int /*<<< orphan*/  functions ; 
 int /*<<< orphan*/  inFromCl ; 
 int /*<<< orphan*/  inh ; 
 int /*<<< orphan*/  insertedCols ; 
 int /*<<< orphan*/  joinaliasvars ; 
 int /*<<< orphan*/  jointype ; 
 int /*<<< orphan*/  lateral ; 
 int /*<<< orphan*/  relid ; 
 int /*<<< orphan*/  relkind ; 
 int /*<<< orphan*/  rellockmode ; 
 int /*<<< orphan*/  requiredPerms ; 
 int /*<<< orphan*/  rtekind ; 
 int /*<<< orphan*/  securityQuals ; 
 int /*<<< orphan*/  security_barrier ; 
 int /*<<< orphan*/  selectedCols ; 
 int /*<<< orphan*/  self_reference ; 
 int /*<<< orphan*/  subquery ; 
 int /*<<< orphan*/  tablefunc ; 
 int /*<<< orphan*/  tablesample ; 
 int /*<<< orphan*/  updatedCols ; 
 int /*<<< orphan*/  values_lists ; 

__attribute__((used)) static bool
_equalRangeTblEntry(const RangeTblEntry *a, const RangeTblEntry *b)
{
	COMPARE_SCALAR_FIELD(rtekind);
	COMPARE_SCALAR_FIELD(relid);
	COMPARE_SCALAR_FIELD(relkind);
	COMPARE_SCALAR_FIELD(rellockmode);
	COMPARE_NODE_FIELD(tablesample);
	COMPARE_NODE_FIELD(subquery);
	COMPARE_SCALAR_FIELD(security_barrier);
	COMPARE_SCALAR_FIELD(jointype);
	COMPARE_NODE_FIELD(joinaliasvars);
	COMPARE_NODE_FIELD(functions);
	COMPARE_SCALAR_FIELD(funcordinality);
	COMPARE_NODE_FIELD(tablefunc);
	COMPARE_NODE_FIELD(values_lists);
	COMPARE_STRING_FIELD(ctename);
	COMPARE_SCALAR_FIELD(ctelevelsup);
	COMPARE_SCALAR_FIELD(self_reference);
	COMPARE_NODE_FIELD(coltypes);
	COMPARE_NODE_FIELD(coltypmods);
	COMPARE_NODE_FIELD(colcollations);
	COMPARE_STRING_FIELD(enrname);
	COMPARE_SCALAR_FIELD(enrtuples);
	COMPARE_NODE_FIELD(alias);
	COMPARE_NODE_FIELD(eref);
	COMPARE_SCALAR_FIELD(lateral);
	COMPARE_SCALAR_FIELD(inh);
	COMPARE_SCALAR_FIELD(inFromCl);
	COMPARE_SCALAR_FIELD(requiredPerms);
	COMPARE_SCALAR_FIELD(checkAsUser);
	COMPARE_BITMAPSET_FIELD(selectedCols);
	COMPARE_BITMAPSET_FIELD(insertedCols);
	COMPARE_BITMAPSET_FIELD(updatedCols);
	COMPARE_BITMAPSET_FIELD(extraUpdatedCols);
	COMPARE_NODE_FIELD(securityQuals);

	return true;
}