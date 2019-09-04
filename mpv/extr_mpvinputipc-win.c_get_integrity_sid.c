#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Sid; } ;
struct TYPE_7__ {TYPE_1__ Label; } ;
typedef  TYPE_2__ TOKEN_MANDATORY_LABEL ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  ConvertSidToStringSidA (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetTokenInformation (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  TOKEN_QUERY ; 
 int /*<<< orphan*/  TokenIntegrityLevel ; 
 int /*<<< orphan*/  talloc_free (TYPE_2__*) ; 
 TYPE_2__* talloc_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *get_integrity_sid(void)
{
    char *ssid = NULL;
    TOKEN_MANDATORY_LABEL *info = NULL;
    HANDLE t;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &t))
        goto done;

    DWORD info_len;
    if (!GetTokenInformation(t, TokenIntegrityLevel, NULL, 0, &info_len) &&
        GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        goto done;

    info = talloc_size(NULL, info_len);
    if (!GetTokenInformation(t, TokenIntegrityLevel, info, info_len, &info_len))
        goto done;
    if (!info->Label.Sid)
        goto done;

    ConvertSidToStringSidA(info->Label.Sid, &ssid);
done:
    if (t)
        CloseHandle(t);
    talloc_free(info);
    return ssid;
}