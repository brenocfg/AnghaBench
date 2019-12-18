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
typedef  int /*<<< orphan*/  NamedArgExpr ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg ; 
 int /*<<< orphan*/  argnumber ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  name ; 

__attribute__((used)) static bool
_equalNamedArgExpr(const NamedArgExpr *a, const NamedArgExpr *b)
{
	COMPARE_NODE_FIELD(arg);
	COMPARE_STRING_FIELD(name);
	COMPARE_SCALAR_FIELD(argnumber);
	COMPARE_LOCATION_FIELD(location);

	return true;
}