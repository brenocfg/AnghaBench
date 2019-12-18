#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int contype; int /*<<< orphan*/  location; } ;
struct TYPE_6__ {void* fkconstraints; int /*<<< orphan*/  pstate; int /*<<< orphan*/  isforeign; void* ckconstraints; void* ixconstraints; int /*<<< orphan*/  ispartitioned; } ;
typedef  TYPE_1__ CreateStmtContext ;
typedef  TYPE_2__ Constraint ;

/* Variables and functions */
#define  CONSTR_ATTR_DEFERRABLE 139 
#define  CONSTR_ATTR_DEFERRED 138 
#define  CONSTR_ATTR_IMMEDIATE 137 
#define  CONSTR_ATTR_NOT_DEFERRABLE 136 
#define  CONSTR_CHECK 135 
#define  CONSTR_DEFAULT 134 
#define  CONSTR_EXCLUSION 133 
#define  CONSTR_FOREIGN 132 
#define  CONSTR_NOTNULL 131 
#define  CONSTR_NULL 130 
#define  CONSTR_PRIMARY 129 
#define  CONSTR_UNIQUE 128 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 void* lappend (void*,TYPE_2__*) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
transformTableConstraint(CreateStmtContext *cxt, Constraint *constraint)
{
	switch (constraint->contype)
	{
		case CONSTR_PRIMARY:
			if (cxt->isforeign)
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("primary key constraints are not supported on foreign tables"),
						 parser_errposition(cxt->pstate,
											constraint->location)));
			cxt->ixconstraints = lappend(cxt->ixconstraints, constraint);
			break;

		case CONSTR_UNIQUE:
			if (cxt->isforeign)
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("unique constraints are not supported on foreign tables"),
						 parser_errposition(cxt->pstate,
											constraint->location)));
			cxt->ixconstraints = lappend(cxt->ixconstraints, constraint);
			break;

		case CONSTR_EXCLUSION:
			if (cxt->isforeign)
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("exclusion constraints are not supported on foreign tables"),
						 parser_errposition(cxt->pstate,
											constraint->location)));
			if (cxt->ispartitioned)
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("exclusion constraints are not supported on partitioned tables"),
						 parser_errposition(cxt->pstate,
											constraint->location)));
			cxt->ixconstraints = lappend(cxt->ixconstraints, constraint);
			break;

		case CONSTR_CHECK:
			cxt->ckconstraints = lappend(cxt->ckconstraints, constraint);
			break;

		case CONSTR_FOREIGN:
			if (cxt->isforeign)
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("foreign key constraints are not supported on foreign tables"),
						 parser_errposition(cxt->pstate,
											constraint->location)));
			cxt->fkconstraints = lappend(cxt->fkconstraints, constraint);
			break;

		case CONSTR_NULL:
		case CONSTR_NOTNULL:
		case CONSTR_DEFAULT:
		case CONSTR_ATTR_DEFERRABLE:
		case CONSTR_ATTR_NOT_DEFERRABLE:
		case CONSTR_ATTR_DEFERRED:
		case CONSTR_ATTR_IMMEDIATE:
			elog(ERROR, "invalid context for constraint type %d",
				 constraint->contype);
			break;

		default:
			elog(ERROR, "unrecognized constraint type: %d",
				 constraint->contype);
			break;
	}
}