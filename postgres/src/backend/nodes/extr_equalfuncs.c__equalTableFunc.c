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
typedef  int /*<<< orphan*/  TableFunc ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  colcollations ; 
 int /*<<< orphan*/  coldefexprs ; 
 int /*<<< orphan*/  colexprs ; 
 int /*<<< orphan*/  colnames ; 
 int /*<<< orphan*/  coltypes ; 
 int /*<<< orphan*/  coltypmods ; 
 int /*<<< orphan*/  docexpr ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  notnulls ; 
 int /*<<< orphan*/  ns_names ; 
 int /*<<< orphan*/  ns_uris ; 
 int /*<<< orphan*/  ordinalitycol ; 
 int /*<<< orphan*/  rowexpr ; 

__attribute__((used)) static bool
_equalTableFunc(const TableFunc *a, const TableFunc *b)
{
	COMPARE_NODE_FIELD(ns_uris);
	COMPARE_NODE_FIELD(ns_names);
	COMPARE_NODE_FIELD(docexpr);
	COMPARE_NODE_FIELD(rowexpr);
	COMPARE_NODE_FIELD(colnames);
	COMPARE_NODE_FIELD(coltypes);
	COMPARE_NODE_FIELD(coltypmods);
	COMPARE_NODE_FIELD(colcollations);
	COMPARE_NODE_FIELD(colexprs);
	COMPARE_NODE_FIELD(coldefexprs);
	COMPARE_BITMAPSET_FIELD(notnulls);
	COMPARE_SCALAR_FIELD(ordinalitycol);
	COMPARE_LOCATION_FIELD(location);

	return true;
}