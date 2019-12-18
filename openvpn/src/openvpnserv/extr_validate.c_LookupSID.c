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
typedef  int /*<<< orphan*/  SID_NAME_USE ;
typedef  int /*<<< orphan*/  PSID ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LookupAccountName (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_NAME ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _countof (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
LookupSID(const WCHAR *name, PSID sid, DWORD sid_size)
{
    SID_NAME_USE su;
    WCHAR domain[MAX_NAME];
    DWORD dlen = _countof(domain);

    if (!LookupAccountName(NULL, name, sid, &sid_size, domain, &dlen, &su))
    {
        return FALSE; /* not fatal as the group may not exist */
    }
    return TRUE;
}