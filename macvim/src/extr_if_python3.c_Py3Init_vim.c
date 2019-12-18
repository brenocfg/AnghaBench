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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_2__ {char* member_0; int /*<<< orphan*/ * member_1; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyModule_Create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PySys_SetArgv (int,int /*<<< orphan*/ **) ; 
 scalar_t__ init_sys_path () ; 
 scalar_t__ init_types () ; 
 scalar_t__ populate_module (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vim_module ; 
 int /*<<< orphan*/  vimmodule ; 

__attribute__((used)) static PyObject *
Py3Init_vim(void)
{
    /* The special value is removed from sys.path in Python3_Init(). */
    static wchar_t *(argv[2]) = {L"/must>not&exist/foo", NULL};

    if (init_types())
	return NULL;

    /* Set sys.argv[] to avoid a crash in warn(). */
    PySys_SetArgv(1, argv);

    if ((vim_module = PyModule_Create(&vimmodule)) == NULL)
	return NULL;

    if (populate_module(vim_module))
	return NULL;

    if (init_sys_path())
	return NULL;

    return vim_module;
}