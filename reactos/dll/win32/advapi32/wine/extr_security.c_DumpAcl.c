#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_5__ {int AceCount; } ;
typedef  TYPE_1__* PACL ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DumpAce (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpString (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetAce (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsValidAcl (TYPE_1__*) ; 
 int /*<<< orphan*/  SDDL_AUTO_INHERITED ; 
 int /*<<< orphan*/  SDDL_AUTO_INHERIT_REQ ; 
 int /*<<< orphan*/  SDDL_PROTECTED ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static BOOL DumpAcl(PACL pacl, WCHAR **pwptr, ULONG *plen, BOOL protected, BOOL autoInheritReq, BOOL autoInherited)
{
    WORD count;
    int i;

    if (protected)
        DumpString(SDDL_PROTECTED, -1, pwptr, plen);
    if (autoInheritReq)
        DumpString(SDDL_AUTO_INHERIT_REQ, -1, pwptr, plen);
    if (autoInherited)
        DumpString(SDDL_AUTO_INHERITED, -1, pwptr, plen);

    if (pacl == NULL)
        return TRUE;

    if (!IsValidAcl(pacl))
        return FALSE;

    count = pacl->AceCount;
    for (i = 0; i < count; i++)
    {
        LPVOID ace;
        if (!GetAce(pacl, i, &ace))
            return FALSE;
        if (!DumpAce(ace, pwptr, plen))
            return FALSE;
    }

    return TRUE;
}