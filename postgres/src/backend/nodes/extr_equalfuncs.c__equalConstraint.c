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
typedef  int /*<<< orphan*/  Constraint ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  access_method ; 
 int /*<<< orphan*/  conname ; 
 int /*<<< orphan*/  contype ; 
 int /*<<< orphan*/  cooked_expr ; 
 int /*<<< orphan*/  deferrable ; 
 int /*<<< orphan*/  exclusions ; 
 int /*<<< orphan*/  fk_attrs ; 
 int /*<<< orphan*/  fk_del_action ; 
 int /*<<< orphan*/  fk_matchtype ; 
 int /*<<< orphan*/  fk_upd_action ; 
 int /*<<< orphan*/  generated_when ; 
 int /*<<< orphan*/  including ; 
 int /*<<< orphan*/  indexname ; 
 int /*<<< orphan*/  indexspace ; 
 int /*<<< orphan*/  initdeferred ; 
 int /*<<< orphan*/  initially_valid ; 
 int /*<<< orphan*/  is_no_inherit ; 
 int /*<<< orphan*/  keys ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  old_conpfeqop ; 
 int /*<<< orphan*/  old_pktable_oid ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  pk_attrs ; 
 int /*<<< orphan*/  pktable ; 
 int /*<<< orphan*/  raw_expr ; 
 int /*<<< orphan*/  reset_default_tblspc ; 
 int /*<<< orphan*/  skip_validation ; 
 int /*<<< orphan*/  where_clause ; 

__attribute__((used)) static bool
_equalConstraint(const Constraint *a, const Constraint *b)
{
	COMPARE_SCALAR_FIELD(contype);
	COMPARE_STRING_FIELD(conname);
	COMPARE_SCALAR_FIELD(deferrable);
	COMPARE_SCALAR_FIELD(initdeferred);
	COMPARE_LOCATION_FIELD(location);
	COMPARE_SCALAR_FIELD(is_no_inherit);
	COMPARE_NODE_FIELD(raw_expr);
	COMPARE_STRING_FIELD(cooked_expr);
	COMPARE_SCALAR_FIELD(generated_when);
	COMPARE_NODE_FIELD(keys);
	COMPARE_NODE_FIELD(including);
	COMPARE_NODE_FIELD(exclusions);
	COMPARE_NODE_FIELD(options);
	COMPARE_STRING_FIELD(indexname);
	COMPARE_STRING_FIELD(indexspace);
	COMPARE_SCALAR_FIELD(reset_default_tblspc);
	COMPARE_STRING_FIELD(access_method);
	COMPARE_NODE_FIELD(where_clause);
	COMPARE_NODE_FIELD(pktable);
	COMPARE_NODE_FIELD(fk_attrs);
	COMPARE_NODE_FIELD(pk_attrs);
	COMPARE_SCALAR_FIELD(fk_matchtype);
	COMPARE_SCALAR_FIELD(fk_upd_action);
	COMPARE_SCALAR_FIELD(fk_del_action);
	COMPARE_NODE_FIELD(old_conpfeqop);
	COMPARE_SCALAR_FIELD(old_pktable_oid);
	COMPARE_SCALAR_FIELD(skip_validation);
	COMPARE_SCALAR_FIELD(initially_valid);

	return true;
}