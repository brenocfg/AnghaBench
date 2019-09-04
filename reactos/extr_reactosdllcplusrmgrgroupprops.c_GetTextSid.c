#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {int* Value; } ;
typedef  TYPE_1__* PSID_IDENTIFIER_AUTHORITY ;
typedef  int /*<<< orphan*/  PSID ;
typedef  scalar_t__ LPTSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 TYPE_1__* GetSidIdentifierAuthority (int /*<<< orphan*/ ) ; 
 scalar_t__* GetSidSubAuthority (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__* GetSidSubAuthorityCount (int /*<<< orphan*/ ) ; 
 scalar_t__ SID_REVISION ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 scalar_t__ lstrlen (scalar_t__) ; 
 scalar_t__ wsprintf (scalar_t__,int /*<<< orphan*/ ,scalar_t__,...) ; 

__attribute__((used)) static VOID
GetTextSid(PSID pSid,
           LPTSTR pTextSid)
{
    PSID_IDENTIFIER_AUTHORITY psia;
    DWORD dwSubAuthorities;
    DWORD dwSidRev = SID_REVISION;
    DWORD dwCounter;
    DWORD dwSidSize;

    psia = GetSidIdentifierAuthority(pSid);

    dwSubAuthorities = *GetSidSubAuthorityCount(pSid);

    dwSidSize = wsprintf(pTextSid, TEXT("S-%lu-"), dwSidRev);

    if ((psia->Value[0] != 0) || (psia->Value[1] != 0))
    {
        dwSidSize += wsprintf(pTextSid + lstrlen(pTextSid),
                              TEXT("0x%02hx%02hx%02hx%02hx%02hx%02hx"),
                              (USHORT)psia->Value[0],
                              (USHORT)psia->Value[1],
                              (USHORT)psia->Value[2],
                              (USHORT)psia->Value[3],
                              (USHORT)psia->Value[4],
                              (USHORT)psia->Value[5]);
    }
    else
    {
        dwSidSize += wsprintf(pTextSid + lstrlen(pTextSid),
                              TEXT("%lu"),
                              (ULONG)(psia->Value[5]) +
                              (ULONG)(psia->Value[4] <<  8) +
                              (ULONG)(psia->Value[3] << 16) +
                              (ULONG)(psia->Value[2] << 24));
    }

    for (dwCounter = 0 ; dwCounter < dwSubAuthorities ; dwCounter++)
    {
        dwSidSize += wsprintf(pTextSid + dwSidSize, TEXT("-%lu"),
                              *GetSidSubAuthority(pSid, dwCounter));
    }
}