#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  location; int /*<<< orphan*/  number; } ;
struct TYPE_8__ {int /*<<< orphan*/ * (* p_paramref_hook ) (TYPE_1__*,TYPE_2__*) ;} ;
typedef  TYPE_1__ ParseState ;
typedef  TYPE_2__ ParamRef ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_PARAMETER ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser_errposition (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static Node *
transformParamRef(ParseState *pstate, ParamRef *pref)
{
	Node	   *result;

	/*
	 * The core parser knows nothing about Params.  If a hook is supplied,
	 * call it.  If not, or if the hook returns NULL, throw a generic error.
	 */
	if (pstate->p_paramref_hook != NULL)
		result = pstate->p_paramref_hook(pstate, pref);
	else
		result = NULL;

	if (result == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_PARAMETER),
				 errmsg("there is no parameter $%d", pref->number),
				 parser_errposition(pstate, pref->location)));

	return result;
}