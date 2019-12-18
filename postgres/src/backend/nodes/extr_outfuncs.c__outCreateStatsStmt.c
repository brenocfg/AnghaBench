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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  CreateStatsStmt ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defnames ; 
 int /*<<< orphan*/  exprs ; 
 int /*<<< orphan*/  if_not_exists ; 
 int /*<<< orphan*/  relations ; 
 int /*<<< orphan*/  stat_types ; 
 int /*<<< orphan*/  stxcomment ; 

__attribute__((used)) static void
_outCreateStatsStmt(StringInfo str, const CreateStatsStmt *node)
{
	WRITE_NODE_TYPE("CREATESTATSSTMT");

	WRITE_NODE_FIELD(defnames);
	WRITE_NODE_FIELD(stat_types);
	WRITE_NODE_FIELD(exprs);
	WRITE_NODE_FIELD(relations);
	WRITE_STRING_FIELD(stxcomment);
	WRITE_BOOL_FIELD(if_not_exists);
}