#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ pathtarget; TYPE_1__* param_info; TYPE_2__* parent; } ;
struct TYPE_6__ {scalar_t__ reltarget; int /*<<< orphan*/ * relids; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ppi_req_outer; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_3__ Path ;

/* Variables and functions */
 int /*<<< orphan*/  NodeTag ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_FLOAT_FIELD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  outBitmapset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parallel_aware ; 
 int /*<<< orphan*/  parallel_safe ; 
 int /*<<< orphan*/  parallel_workers ; 
 int /*<<< orphan*/  pathkeys ; 
 int /*<<< orphan*/  pathtarget ; 
 int /*<<< orphan*/  pathtype ; 
 int /*<<< orphan*/  rows ; 
 int /*<<< orphan*/  startup_cost ; 
 int /*<<< orphan*/  total_cost ; 

__attribute__((used)) static void
_outPathInfo(StringInfo str, const Path *node)
{
	WRITE_ENUM_FIELD(pathtype, NodeTag);
	appendStringInfoString(str, " :parent_relids ");
	outBitmapset(str, node->parent->relids);
	if (node->pathtarget != node->parent->reltarget)
		WRITE_NODE_FIELD(pathtarget);
	appendStringInfoString(str, " :required_outer ");
	if (node->param_info)
		outBitmapset(str, node->param_info->ppi_req_outer);
	else
		outBitmapset(str, NULL);
	WRITE_BOOL_FIELD(parallel_aware);
	WRITE_BOOL_FIELD(parallel_safe);
	WRITE_INT_FIELD(parallel_workers);
	WRITE_FLOAT_FIELD(rows, "%.0f");
	WRITE_FLOAT_FIELD(startup_cost, "%.2f");
	WRITE_FLOAT_FIELD(total_cost, "%.2f");
	WRITE_NODE_FIELD(pathkeys);
}