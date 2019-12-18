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
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refassgnexpr ; 
 int /*<<< orphan*/  refcollid ; 
 int /*<<< orphan*/  refcontainertype ; 
 int /*<<< orphan*/  refelemtype ; 
 int /*<<< orphan*/  refexpr ; 
 int /*<<< orphan*/  reflowerindexpr ; 
 int /*<<< orphan*/  reftypmod ; 
 int /*<<< orphan*/  refupperindexpr ; 

__attribute__((used)) static void
_outSubscriptingRef(StringInfo str, const SubscriptingRef *node)
{
	WRITE_NODE_TYPE("SUBSCRIPTINGREF");

	WRITE_OID_FIELD(refcontainertype);
	WRITE_OID_FIELD(refelemtype);
	WRITE_INT_FIELD(reftypmod);
	WRITE_OID_FIELD(refcollid);
	WRITE_NODE_FIELD(refupperindexpr);
	WRITE_NODE_FIELD(reflowerindexpr);
	WRITE_NODE_FIELD(refexpr);
	WRITE_NODE_FIELD(refassgnexpr);
}