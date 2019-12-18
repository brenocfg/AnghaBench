#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_2__* funcexpr; } ;
struct TYPE_16__ {int /*<<< orphan*/  name; } ;
struct TYPE_15__ {int /*<<< orphan*/  portalname; int /*<<< orphan*/  ismove; } ;
struct TYPE_14__ {int /*<<< orphan*/  tupDesc; } ;
struct TYPE_13__ {TYPE_1__* plansource; } ;
struct TYPE_12__ {int /*<<< orphan*/  funcresulttype; } ;
struct TYPE_11__ {int /*<<< orphan*/  resultDesc; } ;
typedef  TYPE_3__ PreparedStatement ;
typedef  TYPE_4__* Portal ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_5__ FetchStmt ;
typedef  TYPE_6__ ExecuteStmt ;
typedef  TYPE_7__ CallStmt ;

/* Variables and functions */
 TYPE_3__* FetchPreparedStatement (int /*<<< orphan*/ ,int) ; 
 TYPE_4__* GetPortalByName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PortalIsValid (TYPE_4__*) ; 
 int /*<<< orphan*/  RECORDOID ; 
#define  T_CallStmt 132 
#define  T_ExecuteStmt 131 
#define  T_ExplainStmt 130 
#define  T_FetchStmt 129 
#define  T_VariableShowStmt 128 
 int nodeTag (int /*<<< orphan*/ *) ; 

bool
UtilityReturnsTuples(Node *parsetree)
{
	switch (nodeTag(parsetree))
	{
		case T_CallStmt:
			{
				CallStmt   *stmt = (CallStmt *) parsetree;

				return (stmt->funcexpr->funcresulttype == RECORDOID);
			}
		case T_FetchStmt:
			{
				FetchStmt  *stmt = (FetchStmt *) parsetree;
				Portal		portal;

				if (stmt->ismove)
					return false;
				portal = GetPortalByName(stmt->portalname);
				if (!PortalIsValid(portal))
					return false;	/* not our business to raise error */
				return portal->tupDesc ? true : false;
			}

		case T_ExecuteStmt:
			{
				ExecuteStmt *stmt = (ExecuteStmt *) parsetree;
				PreparedStatement *entry;

				entry = FetchPreparedStatement(stmt->name, false);
				if (!entry)
					return false;	/* not our business to raise error */
				if (entry->plansource->resultDesc)
					return true;
				return false;
			}

		case T_ExplainStmt:
			return true;

		case T_VariableShowStmt:
			return true;

		default:
			return false;
	}
}