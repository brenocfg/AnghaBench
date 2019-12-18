#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* data; } ;
struct TYPE_10__ {char* errormsg; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Step ;
typedef  TYPE_2__ PQExpBufferData ;

/* Variables and functions */
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  report_error_message (TYPE_1__*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

__attribute__((used)) static void
report_multiple_error_messages(Step *step, int nextra, Step **extrastep)
{
	PQExpBufferData buffer;
	int			n;

	if (nextra == 0)
	{
		report_error_message(step);
		return;
	}

	initPQExpBuffer(&buffer);
	appendPQExpBufferStr(&buffer, step->name);

	for (n = 0; n < nextra; ++n)
		appendPQExpBuffer(&buffer, " %s", extrastep[n]->name);

	if (step->errormsg)
	{
		fprintf(stdout, "error in steps %s: %s\n", buffer.data,
				step->errormsg);
		free(step->errormsg);
		step->errormsg = NULL;
	}

	for (n = 0; n < nextra; ++n)
	{
		if (extrastep[n]->errormsg == NULL)
			continue;
		fprintf(stdout, "error in steps %s: %s\n",
				buffer.data, extrastep[n]->errormsg);
		free(extrastep[n]->errormsg);
		extrastep[n]->errormsg = NULL;
	}

	termPQExpBuffer(&buffer);
}