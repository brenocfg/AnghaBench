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
typedef  char wchar_t ;
struct dstr {char* array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  argv ;

/* Variables and functions */
 int /*<<< orphan*/  PyEval_InitThreads () ; 
 int /*<<< orphan*/  PyEval_ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyEval_ThreadsInitialized () ; 
 int /*<<< orphan*/  PyGILState_GetThisThreadState () ; 
 int /*<<< orphan*/  PyImport_ImportModule (char*) ; 
 scalar_t__ PyRun_SimpleString (char*) ; 
 int /*<<< orphan*/  PySys_SetArgv (int,char**) ; 
 int /*<<< orphan*/  Py_Initialize () ; 
 int /*<<< orphan*/  Py_IsInitialized () ; 
 int /*<<< orphan*/  Py_SetPythonHome (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCRIPT_DIR ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (char const*) ; 
 int /*<<< orphan*/  _putenv (char*) ; 
 int /*<<< orphan*/  add_hook_functions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_python_frontend_funcs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_to_python_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfree (scalar_t__*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_printf (struct dstr*,char*,char*) ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  home_path ; 
 int /*<<< orphan*/  import_python (char const*) ; 
 int /*<<< orphan*/  obs_add_tick_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_python_unload () ; 
 int /*<<< orphan*/  os_utf8_to_wcs (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  py_error () ; 
 int /*<<< orphan*/  py_obspython ; 
 int python_loaded ; 
 int python_loaded_at_all ; 
 int /*<<< orphan*/  python_tick ; 
 scalar_t__* pythondir ; 
 char* startup_script ; 
 int /*<<< orphan*/  warn (char*) ; 

bool obs_scripting_load_python(const char *python_path)
{
	if (python_loaded)
		return true;

		/* Use external python on windows and mac */
#if RUNTIME_LINK
#if 0
	struct dstr old_path  = {0};
	struct dstr new_path  = {0};
#endif

	if (!import_python(python_path))
		return false;

	if (python_path && *python_path) {
		os_utf8_to_wcs(python_path, 0, home_path, 1024);
		Py_SetPythonHome(home_path);
#if 0
		dstr_copy(&old_path, getenv("PATH"));
		_putenv("PYTHONPATH=");
		_putenv("PATH=");
#endif
	}
#else
	UNUSED_PARAMETER(python_path);
#endif

	Py_Initialize();
	if (!Py_IsInitialized())
		return false;

#if 0
#ifdef _DEBUG
	if (pythondir && *pythondir) {
		dstr_printf(&new_path, "PATH=%s", old_path.array);
		_putenv(new_path.array);
	}
#endif

	bfree(pythondir);
	dstr_free(&new_path);
	dstr_free(&old_path);
#endif

	PyEval_InitThreads();
	if (!PyEval_ThreadsInitialized())
		return false;

	/* ---------------------------------------------- */
	/* Must set arguments for guis to work            */

	wchar_t *argv[] = {L"", NULL};
	int argc = sizeof(argv) / sizeof(wchar_t *) - 1;

	PySys_SetArgv(argc, argv);

#ifdef DEBUG_PYTHON_STARTUP
	/* ---------------------------------------------- */
	/* Debug logging to file if startup is failing    */

	PyRun_SimpleString("import os");
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("os.environ['PYTHONUNBUFFERED'] = '1'");
	PyRun_SimpleString("sys.stdout = open('./stdOut.txt','w',1)");
	PyRun_SimpleString("sys.stderr = open('./stdErr.txt','w',1)");
	PyRun_SimpleString("print(sys.version)");
#endif

	/* ---------------------------------------------- */
	/* Load main interface module                     */

	add_to_python_path(SCRIPT_DIR);

	py_obspython = PyImport_ImportModule("obspython");
	bool success = !py_error();
	if (!success) {
		warn("Error importing obspython.py', unloading obs-python");
		goto out;
	}

	python_loaded = PyRun_SimpleString(startup_script) == 0;
	py_error();

	add_hook_functions(py_obspython);
	py_error();

	add_python_frontend_funcs(py_obspython);
	py_error();

out:
	/* ---------------------------------------------- */
	/* Free data                                      */

	PyEval_ReleaseThread(PyGILState_GetThisThreadState());

	if (!success) {
		warn("Failed to load python plugin");
		obs_python_unload();
	}

	python_loaded_at_all = success;

	if (python_loaded)
		obs_add_tick_callback(python_tick, NULL);

	return python_loaded;
}