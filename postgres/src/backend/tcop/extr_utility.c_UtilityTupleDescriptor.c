#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ VariableShowStmt ;
typedef  int /*<<< orphan*/ * TupleDesc ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  portalname; int /*<<< orphan*/  ismove; } ;
struct TYPE_8__ {int /*<<< orphan*/  tupDesc; } ;
typedef  int /*<<< orphan*/  PreparedStatement ;
typedef  TYPE_2__* Portal ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_3__ FetchStmt ;
typedef  int /*<<< orphan*/  ExplainStmt ;
typedef  TYPE_4__ ExecuteStmt ;
typedef  int /*<<< orphan*/  CallStmt ;

/* Variables and functions */
 int /*<<< orphan*/ * CallStmtResultDesc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateTupleDescCopy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ExplainResultDesc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FetchPreparedStatement (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * FetchPreparedStatementResultDesc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetPGVariableResultDesc (int /*<<< orphan*/ ) ; 
 TYPE_2__* GetPortalByName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PortalIsValid (TYPE_2__*) ; 
#define  T_CallStmt 132 
#define  T_ExecuteStmt 131 
#define  T_ExplainStmt 130 
#define  T_FetchStmt 129 
#define  T_VariableShowStmt 128 
 int nodeTag (int /*<<< orphan*/ *) ; 

TupleDesc
UtilityTupleDescriptor(Node *parsetree)
{
	switch (nodeTag(parsetree))
	{
		case T_CallStmt:
			return CallStmtResultDesc((CallStmt *) parsetree);

		case T_FetchStmt:
			{
				FetchStmt  *stmt = (FetchStmt *) parsetree;
				Portal		portal;

				if (stmt->ismove)
					return NULL;
				portal = GetPortalByName(stmt->portalname);
				if (!PortalIsValid(portal))
					return NULL;	/* not our business to raise error */
				return CreateTupleDescCopy(portal->tupDesc);
			}

		case T_ExecuteStmt:
			{
				ExecuteStmt *stmt = (ExecuteStmt *) parsetree;
				PreparedStatement *entry;

				entry = FetchPreparedStatement(stmt->name, false);
				if (!entry)
					return NULL;	/* not our business to raise error */
				return FetchPreparedStatementResultDesc(entry);
			}

		case T_ExplainStmt:
			return ExplainResultDesc((ExplainStmt *) parsetree);

		case T_VariableShowStmt:
			{
				VariableShowStmt *n = (VariableShowStmt *) parsetree;

				return GetPGVariableResultDesc(n->name);
			}

		default:
			return NULL;
	}
}