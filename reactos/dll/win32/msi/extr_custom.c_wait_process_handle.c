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
typedef  int UINT ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int custom_get_process_return (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_running_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_dialog_check_messages (int /*<<< orphan*/ ) ; 
 int msidbCustomActionTypeAsync ; 
 int msidbCustomActionTypeContinue ; 

__attribute__((used)) static UINT wait_process_handle(MSIPACKAGE* package, UINT type,
                           HANDLE ProcessHandle, LPCWSTR name)
{
    UINT rc = ERROR_SUCCESS;

    if (!(type & msidbCustomActionTypeAsync))
    {
        TRACE("waiting for %s\n", debugstr_w(name));

        msi_dialog_check_messages(ProcessHandle);

        if (!(type & msidbCustomActionTypeContinue))
            rc = custom_get_process_return(ProcessHandle);

        CloseHandle(ProcessHandle);
    }
    else
    {
        TRACE("%s running in background\n", debugstr_w(name));

        if (!(type & msidbCustomActionTypeContinue))
            file_running_action(package, ProcessHandle, TRUE, name);
        else
            CloseHandle(ProcessHandle);
    }

    return rc;
}