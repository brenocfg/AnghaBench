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
typedef  int /*<<< orphan*/  WindowFunc ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aggfilter ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  inputcollid ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  winagg ; 
 int /*<<< orphan*/  wincollid ; 
 int /*<<< orphan*/  winfnoid ; 
 int /*<<< orphan*/  winref ; 
 int /*<<< orphan*/  winstar ; 
 int /*<<< orphan*/  wintype ; 

__attribute__((used)) static void
_outWindowFunc(StringInfo str, const WindowFunc *node)
{
	WRITE_NODE_TYPE("WINDOWFUNC");

	WRITE_OID_FIELD(winfnoid);
	WRITE_OID_FIELD(wintype);
	WRITE_OID_FIELD(wincollid);
	WRITE_OID_FIELD(inputcollid);
	WRITE_NODE_FIELD(args);
	WRITE_NODE_FIELD(aggfilter);
	WRITE_UINT_FIELD(winref);
	WRITE_BOOL_FIELD(winstar);
	WRITE_BOOL_FIELD(winagg);
	WRITE_LOCATION_FIELD(location);
}