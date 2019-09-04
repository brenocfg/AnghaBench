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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  ITaskFolder ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  ITaskFolder_DeleteTask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITaskFolder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SysAllocString (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f_optW ; 
 int /*<<< orphan*/ * get_tasks_root_folder () ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tn_optW ; 

__attribute__((used)) static int delete_command(int argc, WCHAR *argv[])
{
    const WCHAR *task_name = NULL;
    ITaskFolder *root = NULL;
    BSTR str;
    HRESULT hres;

    while (argc) {
        if (!strcmpiW(argv[0], f_optW)) {
            TRACE("force opt\n");
            argc--;
            argv++;
        }else if(!strcmpiW(argv[0], tn_optW)) {
            if (argc < 2) {
                FIXME("Missing /tn value\n");
                return 1;
            }

            if (task_name) {
                FIXME("Duplicated /tn argument\n");
                return 1;
            }

            task_name = argv[1];
            argc -= 2;
            argv += 2;
        }else {
            FIXME("Unsupported argument %s\n", debugstr_w(argv[0]));
            return 1;
        }
    }

    if (!task_name) {
        FIXME("Missing /tn argument\n");
        return 1;
    }

    root = get_tasks_root_folder();
    if (!root)
        return 1;

    str = SysAllocString(task_name);
    hres = ITaskFolder_DeleteTask(root, str, 0);
    SysFreeString(str);
    ITaskFolder_Release(root);
    if (FAILED(hres))
        return 1;

    return 0;
}