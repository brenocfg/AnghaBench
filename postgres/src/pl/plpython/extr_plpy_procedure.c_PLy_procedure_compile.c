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
typedef  int /*<<< orphan*/  call ;
struct TYPE_3__ {char* pyname; scalar_t__ proname; int /*<<< orphan*/ * code; int /*<<< orphan*/  globals; int /*<<< orphan*/  mcxt; int /*<<< orphan*/  src; int /*<<< orphan*/  statics; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PLyProcedure ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextStrdup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  PLy_elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  PLy_interp_globals ; 
 char* PLy_procedure_munge_source (char*,char const*) ; 
 int /*<<< orphan*/  PyDict_Copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyDict_New () ; 
 int /*<<< orphan*/  PyDict_SetItemString (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyRun_String (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_CompileString (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_eval_input ; 
 int /*<<< orphan*/  Py_file_input ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int snprintf (char*,int,char*,char*) ; 

void
PLy_procedure_compile(PLyProcedure *proc, const char *src)
{
	PyObject   *crv = NULL;
	char	   *msrc;

	proc->globals = PyDict_Copy(PLy_interp_globals);

	/*
	 * SD is private preserved data between calls. GD is global data shared by
	 * all functions
	 */
	proc->statics = PyDict_New();
	if (!proc->statics)
		PLy_elog(ERROR, NULL);
	PyDict_SetItemString(proc->globals, "SD", proc->statics);

	/*
	 * insert the function code into the interpreter
	 */
	msrc = PLy_procedure_munge_source(proc->pyname, src);
	/* Save the mangled source for later inclusion in tracebacks */
	proc->src = MemoryContextStrdup(proc->mcxt, msrc);
	crv = PyRun_String(msrc, Py_file_input, proc->globals, NULL);
	pfree(msrc);

	if (crv != NULL)
	{
		int			clen;
		char		call[NAMEDATALEN + 256];

		Py_DECREF(crv);

		/*
		 * compile a call to the function
		 */
		clen = snprintf(call, sizeof(call), "%s()", proc->pyname);
		if (clen < 0 || clen >= sizeof(call))
			elog(ERROR, "string would overflow buffer");
		proc->code = Py_CompileString(call, "<string>", Py_eval_input);
		if (proc->code != NULL)
			return;
	}

	if (proc->proname)
		PLy_elog(ERROR, "could not compile PL/Python function \"%s\"",
				 proc->proname);
	else
		PLy_elog(ERROR, "could not compile anonymous PL/Python code block");
}