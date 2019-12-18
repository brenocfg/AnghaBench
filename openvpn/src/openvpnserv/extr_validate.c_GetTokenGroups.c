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
typedef  int /*<<< orphan*/ * PTOKEN_GROUPS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetTokenInformation (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  MsgToEventLog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TokenGroups ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PTOKEN_GROUPS
GetTokenGroups(const HANDLE token)
{
    PTOKEN_GROUPS groups = NULL;
    DWORD buf_size = 0;

    if (!GetTokenInformation(token, TokenGroups, groups, buf_size, &buf_size)
        && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
    {
        groups = malloc(buf_size);
    }
    if (!groups)
    {
        MsgToEventLog(M_SYSERR, L"GetTokenGroups");
    }
    else if (!GetTokenInformation(token, TokenGroups, groups, buf_size, &buf_size))
    {
        MsgToEventLog(M_SYSERR, L"GetTokenInformation");
        free(groups);
    }
    return groups;
}