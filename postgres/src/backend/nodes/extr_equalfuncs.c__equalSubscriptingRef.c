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
typedef  int /*<<< orphan*/  SubscriptingRef ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refassgnexpr ; 
 int /*<<< orphan*/  refcollid ; 
 int /*<<< orphan*/  refcontainertype ; 
 int /*<<< orphan*/  refelemtype ; 
 int /*<<< orphan*/  refexpr ; 
 int /*<<< orphan*/  reflowerindexpr ; 
 int /*<<< orphan*/  reftypmod ; 
 int /*<<< orphan*/  refupperindexpr ; 

__attribute__((used)) static bool
_equalSubscriptingRef(const SubscriptingRef *a, const SubscriptingRef *b)
{
	COMPARE_SCALAR_FIELD(refcontainertype);
	COMPARE_SCALAR_FIELD(refelemtype);
	COMPARE_SCALAR_FIELD(reftypmod);
	COMPARE_SCALAR_FIELD(refcollid);
	COMPARE_NODE_FIELD(refupperindexpr);
	COMPARE_NODE_FIELD(reflowerindexpr);
	COMPARE_NODE_FIELD(refexpr);
	COMPARE_NODE_FIELD(refassgnexpr);

	return true;
}