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
typedef  int /*<<< orphan*/  IRegisteredTask ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  IRegisteredTask_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRegisteredTask_put_Enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_optW ; 
 int /*<<< orphan*/ * get_registered_task (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tn_optW ; 
 int /*<<< orphan*/  tr_optW ; 

__attribute__((used)) static int change_command(int argc, WCHAR *argv[])
{
    BOOL have_option = FALSE, enable = FALSE;
    const WCHAR *task_name = NULL;
    IRegisteredTask *task;
    HRESULT hres;

    while (argc) {
        if(!strcmpiW(argv[0], tn_optW)) {
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
        }else if (!strcmpiW(argv[0], enable_optW)) {
            enable = TRUE;
            have_option = TRUE;
            argc--;
            argv++;
        }else if (!strcmpiW(argv[0], tr_optW)) {
            if (argc < 2) {
                FIXME("Missing /tr value\n");
                return 1;
            }

            FIXME("Unsupported /tr option %s\n", debugstr_w(argv[1]));
            have_option = TRUE;
            argc -= 2;
            argv += 2;
        }else {
            FIXME("Unsupported arguments %s\n", debugstr_w(argv[0]));
            return 1;
        }
    }

    if (!task_name) {
        FIXME("Missing /tn option\n");
        return 1;
    }

    if (!have_option) {
        FIXME("Missing change options\n");
        return 1;
    }

    task = get_registered_task(task_name);
    if (!task)
        return 1;

    if (enable) {
        hres = IRegisteredTask_put_Enabled(task, VARIANT_TRUE);
        if (FAILED(hres)) {
            IRegisteredTask_Release(task);
            FIXME("put_Enabled failed: %08x\n", hres);
            return 1;
        }
    }

    IRegisteredTask_Release(task);
    return 0;
}