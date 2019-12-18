#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {scalar_t__ hProcess; scalar_t__ hControlPipe; scalar_t__ hToken; int /*<<< orphan*/ * hProfile; int /*<<< orphan*/  ImageListEntry; } ;
typedef  TYPE_1__* PSERVICE_IMAGE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScmEnableBackupRestorePrivileges (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnloadUserProfile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

VOID
ScmRemoveServiceImage(PSERVICE_IMAGE pServiceImage)
{
    DPRINT1("ScmRemoveServiceImage() called\n");

    /* FIXME: Terminate the process */

    /* Remove the service image from the list */
    RemoveEntryList(&pServiceImage->ImageListEntry);

    /* Close the process handle */
    if (pServiceImage->hProcess != INVALID_HANDLE_VALUE)
        CloseHandle(pServiceImage->hProcess);

    /* Close the control pipe */
    if (pServiceImage->hControlPipe != INVALID_HANDLE_VALUE)
        CloseHandle(pServiceImage->hControlPipe);

    /* Unload the user profile */
    if (pServiceImage->hProfile != NULL)
    {
        ScmEnableBackupRestorePrivileges(pServiceImage->hToken, TRUE);
        UnloadUserProfile(pServiceImage->hToken, pServiceImage->hProfile);
        ScmEnableBackupRestorePrivileges(pServiceImage->hToken, FALSE);
    }

    /* Close the logon token */
    if (pServiceImage->hToken != NULL)
        CloseHandle(pServiceImage->hToken);

    /* Release the service image */
    HeapFree(GetProcessHeap(), 0, pServiceImage);
}