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
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PYTHON_API_VERSION ; 
 int /*<<< orphan*/  PySys_SetArgv (int,char**) ; 
 int /*<<< orphan*/  Py_InitModule4 (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VimMethods ; 
 scalar_t__ init_sys_path () ; 
 scalar_t__ init_types () ; 
 scalar_t__ populate_module (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vim_module ; 

__attribute__((used)) static int
PythonMod_Init(void)
{
    /* The special value is removed from sys.path in Python_Init(). */
    static char	*(argv[2]) = {"/must>not&exist/foo", NULL};

    if (init_types())
	return -1;

    /* Set sys.argv[] to avoid a crash in warn(). */
    PySys_SetArgv(1, argv);

    vim_module = Py_InitModule4("vim", VimMethods, (char *)NULL,
				(PyObject *)NULL, PYTHON_API_VERSION);

    if (populate_module(vim_module))
	return -1;

    if (init_sys_path())
	return -1;

    return 0;
}