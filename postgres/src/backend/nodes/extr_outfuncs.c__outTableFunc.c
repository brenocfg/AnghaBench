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
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
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

__attribute__((used)) static void
_outTableFunc(StringInfo str, const TableFunc *node)
{
	WRITE_NODE_TYPE("TABLEFUNC");

	WRITE_NODE_FIELD(ns_uris);
	WRITE_NODE_FIELD(ns_names);
	WRITE_NODE_FIELD(docexpr);
	WRITE_NODE_FIELD(rowexpr);
	WRITE_NODE_FIELD(colnames);
	WRITE_NODE_FIELD(coltypes);
	WRITE_NODE_FIELD(coltypmods);
	WRITE_NODE_FIELD(colcollations);
	WRITE_NODE_FIELD(colexprs);
	WRITE_NODE_FIELD(coldefexprs);
	WRITE_BITMAPSET_FIELD(notnulls);
	WRITE_INT_FIELD(ordinalitycol);
	WRITE_LOCATION_FIELD(location);
}