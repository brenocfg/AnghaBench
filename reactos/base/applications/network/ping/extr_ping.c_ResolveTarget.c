#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hints ;
struct TYPE_7__ {int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_canonname; } ;
struct TYPE_6__ {int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_1__ ADDRINFOW ;

/* Variables and functions */
 int /*<<< orphan*/  AI_CANONNAME ; 
 int /*<<< orphan*/  AI_NUMERICHOST ; 
 int /*<<< orphan*/  CanonName ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Family ; 
 int GetAddrInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__**) ; 
 int GetNameInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDS_UNKNOWN_HOST ; 
 int /*<<< orphan*/  NI_NAMEREQD ; 
 scalar_t__ ResolveAddress ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* Target ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _countof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcsncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
BOOL
ResolveTarget(PCWSTR target)
{
    ADDRINFOW hints;
    int Status;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = Family;
    hints.ai_flags = AI_NUMERICHOST;

    Status = GetAddrInfoW(target, NULL, &hints, &Target);
    if (Status != 0)
    {
        hints.ai_flags = AI_CANONNAME;

        Status = GetAddrInfoW(target, NULL, &hints, &Target);
        if (Status != 0)
        {
            ConResPrintf(StdOut, IDS_UNKNOWN_HOST, target);
            return FALSE;
        }

        wcsncpy(CanonName, Target->ai_canonname, wcslen(Target->ai_canonname));
    }
    else if (ResolveAddress)
    {
        Status = GetNameInfoW(Target->ai_addr, Target->ai_addrlen,
                              CanonName, _countof(CanonName),
                              NULL, 0,
                              NI_NAMEREQD);
        if (Status != 0)
        {
            DPRINT("GetNameInfoW failed: %d\n", WSAGetLastError());
        }
    }

    Family = Target->ai_family;

    return TRUE;
}