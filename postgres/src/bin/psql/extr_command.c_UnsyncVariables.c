#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetVariable (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__ pset ; 

void
UnsyncVariables(void)
{
	SetVariable(pset.vars, "DBNAME", NULL);
	SetVariable(pset.vars, "USER", NULL);
	SetVariable(pset.vars, "HOST", NULL);
	SetVariable(pset.vars, "PORT", NULL);
	SetVariable(pset.vars, "ENCODING", NULL);
	SetVariable(pset.vars, "SERVER_VERSION_NAME", NULL);
	SetVariable(pset.vars, "SERVER_VERSION_NUM", NULL);
}