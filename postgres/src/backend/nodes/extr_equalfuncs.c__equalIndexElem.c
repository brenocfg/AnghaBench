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
typedef  int /*<<< orphan*/  IndexElem ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  collation ; 
 int /*<<< orphan*/  expr ; 
 int /*<<< orphan*/  indexcolname ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  nulls_ordering ; 
 int /*<<< orphan*/  opclass ; 
 int /*<<< orphan*/  ordering ; 

__attribute__((used)) static bool
_equalIndexElem(const IndexElem *a, const IndexElem *b)
{
	COMPARE_STRING_FIELD(name);
	COMPARE_NODE_FIELD(expr);
	COMPARE_STRING_FIELD(indexcolname);
	COMPARE_NODE_FIELD(collation);
	COMPARE_NODE_FIELD(opclass);
	COMPARE_SCALAR_FIELD(ordering);
	COMPARE_SCALAR_FIELD(nulls_ordering);

	return true;
}