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
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DUser ; 
 int /*<<< orphan*/  DenyUserAccess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EditUserAccessRights (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GPerm ; 
 int /*<<< orphan*/  GUser ; 
 int /*<<< orphan*/  GrantUserAccessRights (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OptionD ; 
 int /*<<< orphan*/  OptionE ; 
 scalar_t__ OptionG ; 
 scalar_t__ OptionP ; 
 scalar_t__ OptionR ; 
 int /*<<< orphan*/ * PPerm ; 
 int /*<<< orphan*/  PUser ; 
 int /*<<< orphan*/  RUser ; 
 int /*<<< orphan*/  ReplaceUserAccessRights (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RevokeUserAccessRights (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
ChangeFileACL(LPCTSTR FilePath, LPCTSTR File)
{
    if (OptionG)
    {
        /* Grant specified user access rights. */
        GrantUserAccessRights(FilePath, File, GUser, *GPerm);
    }

    if (OptionP)
    {
        if (!OptionE)
        {
            /* Replace specified user's access rights. */
            ReplaceUserAccessRights(FilePath, File, PUser, *PPerm);
        }
        else
        {
            /* Edit ACL instead of replacing it. */
            EditUserAccessRights(FilePath, File, PUser, *PPerm);
        }
    }

    if (OptionD)
    {
        /* Deny specified user access. */
        DenyUserAccess(FilePath, File, DUser);
    }

    if (OptionR)
    {
        /* Revoke specified user's access rights. */
        RevokeUserAccessRights(FilePath, File, RUser);
    }

    return TRUE;
}