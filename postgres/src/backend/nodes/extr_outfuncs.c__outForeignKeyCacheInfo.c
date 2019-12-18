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
struct TYPE_3__ {int /*<<< orphan*/  nkeys; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ ForeignKeyCacheInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ATTRNUMBER_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  confkey ; 
 int /*<<< orphan*/  confrelid ; 
 int /*<<< orphan*/  conkey ; 
 int /*<<< orphan*/  conoid ; 
 int /*<<< orphan*/  conpfeqop ; 
 int /*<<< orphan*/  conrelid ; 
 int /*<<< orphan*/  nkeys ; 

__attribute__((used)) static void
_outForeignKeyCacheInfo(StringInfo str, const ForeignKeyCacheInfo *node)
{
	WRITE_NODE_TYPE("FOREIGNKEYCACHEINFO");

	WRITE_OID_FIELD(conoid);
	WRITE_OID_FIELD(conrelid);
	WRITE_OID_FIELD(confrelid);
	WRITE_INT_FIELD(nkeys);
	WRITE_ATTRNUMBER_ARRAY(conkey, node->nkeys);
	WRITE_ATTRNUMBER_ARRAY(confkey, node->nkeys);
	WRITE_OID_ARRAY(conpfeqop, node->nkeys);
}