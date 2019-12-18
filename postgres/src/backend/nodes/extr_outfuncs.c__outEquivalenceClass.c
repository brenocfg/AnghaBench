#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* ec_merged; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ EquivalenceClass ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ec_below_outer_join ; 
 int /*<<< orphan*/  ec_broken ; 
 int /*<<< orphan*/  ec_collation ; 
 int /*<<< orphan*/  ec_derives ; 
 int /*<<< orphan*/  ec_has_const ; 
 int /*<<< orphan*/  ec_has_volatile ; 
 int /*<<< orphan*/  ec_max_security ; 
 int /*<<< orphan*/  ec_members ; 
 int /*<<< orphan*/  ec_min_security ; 
 int /*<<< orphan*/  ec_opfamilies ; 
 int /*<<< orphan*/  ec_relids ; 
 int /*<<< orphan*/  ec_sortref ; 
 int /*<<< orphan*/  ec_sources ; 

__attribute__((used)) static void
_outEquivalenceClass(StringInfo str, const EquivalenceClass *node)
{
	/*
	 * To simplify reading, we just chase up to the topmost merged EC and
	 * print that, without bothering to show the merge-ees separately.
	 */
	while (node->ec_merged)
		node = node->ec_merged;

	WRITE_NODE_TYPE("EQUIVALENCECLASS");

	WRITE_NODE_FIELD(ec_opfamilies);
	WRITE_OID_FIELD(ec_collation);
	WRITE_NODE_FIELD(ec_members);
	WRITE_NODE_FIELD(ec_sources);
	WRITE_NODE_FIELD(ec_derives);
	WRITE_BITMAPSET_FIELD(ec_relids);
	WRITE_BOOL_FIELD(ec_has_const);
	WRITE_BOOL_FIELD(ec_has_volatile);
	WRITE_BOOL_FIELD(ec_below_outer_join);
	WRITE_BOOL_FIELD(ec_broken);
	WRITE_UINT_FIELD(ec_sortref);
	WRITE_UINT_FIELD(ec_min_security);
	WRITE_UINT_FIELD(ec_max_security);
}