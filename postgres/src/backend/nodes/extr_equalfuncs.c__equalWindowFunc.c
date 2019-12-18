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

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
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

__attribute__((used)) static bool
_equalWindowFunc(const WindowFunc *a, const WindowFunc *b)
{
	COMPARE_SCALAR_FIELD(winfnoid);
	COMPARE_SCALAR_FIELD(wintype);
	COMPARE_SCALAR_FIELD(wincollid);
	COMPARE_SCALAR_FIELD(inputcollid);
	COMPARE_NODE_FIELD(args);
	COMPARE_NODE_FIELD(aggfilter);
	COMPARE_SCALAR_FIELD(winref);
	COMPARE_SCALAR_FIELD(winstar);
	COMPARE_SCALAR_FIELD(winagg);
	COMPARE_LOCATION_FIELD(location);

	return true;
}