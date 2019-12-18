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
struct TYPE_3__ {int op; void* type; void* typmod; } ;
typedef  TYPE_1__ SQLValueFunction ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 void* DATEOID ; 
 void* NAMEOID ; 
#define  SVFOP_CURRENT_CATALOG 142 
#define  SVFOP_CURRENT_DATE 141 
#define  SVFOP_CURRENT_ROLE 140 
#define  SVFOP_CURRENT_SCHEMA 139 
#define  SVFOP_CURRENT_TIME 138 
#define  SVFOP_CURRENT_TIMESTAMP 137 
#define  SVFOP_CURRENT_TIMESTAMP_N 136 
#define  SVFOP_CURRENT_TIME_N 135 
#define  SVFOP_CURRENT_USER 134 
#define  SVFOP_LOCALTIME 133 
#define  SVFOP_LOCALTIMESTAMP 132 
#define  SVFOP_LOCALTIMESTAMP_N 131 
#define  SVFOP_LOCALTIME_N 130 
#define  SVFOP_SESSION_USER 129 
#define  SVFOP_USER 128 
 void* TIMEOID ; 
 void* TIMESTAMPOID ; 
 void* TIMESTAMPTZOID ; 
 void* TIMETZOID ; 
 void* anytime_typmod_check (int,void*) ; 
 void* anytimestamp_typmod_check (int,void*) ; 

__attribute__((used)) static Node *
transformSQLValueFunction(ParseState *pstate, SQLValueFunction *svf)
{
	/*
	 * All we need to do is insert the correct result type and (where needed)
	 * validate the typmod, so we just modify the node in-place.
	 */
	switch (svf->op)
	{
		case SVFOP_CURRENT_DATE:
			svf->type = DATEOID;
			break;
		case SVFOP_CURRENT_TIME:
			svf->type = TIMETZOID;
			break;
		case SVFOP_CURRENT_TIME_N:
			svf->type = TIMETZOID;
			svf->typmod = anytime_typmod_check(true, svf->typmod);
			break;
		case SVFOP_CURRENT_TIMESTAMP:
			svf->type = TIMESTAMPTZOID;
			break;
		case SVFOP_CURRENT_TIMESTAMP_N:
			svf->type = TIMESTAMPTZOID;
			svf->typmod = anytimestamp_typmod_check(true, svf->typmod);
			break;
		case SVFOP_LOCALTIME:
			svf->type = TIMEOID;
			break;
		case SVFOP_LOCALTIME_N:
			svf->type = TIMEOID;
			svf->typmod = anytime_typmod_check(false, svf->typmod);
			break;
		case SVFOP_LOCALTIMESTAMP:
			svf->type = TIMESTAMPOID;
			break;
		case SVFOP_LOCALTIMESTAMP_N:
			svf->type = TIMESTAMPOID;
			svf->typmod = anytimestamp_typmod_check(false, svf->typmod);
			break;
		case SVFOP_CURRENT_ROLE:
		case SVFOP_CURRENT_USER:
		case SVFOP_USER:
		case SVFOP_SESSION_USER:
		case SVFOP_CURRENT_CATALOG:
		case SVFOP_CURRENT_SCHEMA:
			svf->type = NAMEOID;
			break;
	}

	return (Node *) svf;
}