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
typedef  int /*<<< orphan*/  IRegisteredTask ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITaskFolder_GetTask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITaskFolder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SysAllocString (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_tasks_root_folder () ; 

__attribute__((used)) static IRegisteredTask *get_registered_task(const WCHAR *name)
{
    IRegisteredTask *registered_task;
    ITaskFolder *root;
    BSTR str;
    HRESULT hres;

    root = get_tasks_root_folder();
    if (!root)
        return NULL;

    str = SysAllocString(name);
    hres = ITaskFolder_GetTask(root, str, &registered_task);
    SysFreeString(str);
    ITaskFolder_Release(root);
    if (FAILED(hres)) {
        FIXME("GetTask failed: %08x\n", hres);
        return NULL;
    }

    return registered_task;
}