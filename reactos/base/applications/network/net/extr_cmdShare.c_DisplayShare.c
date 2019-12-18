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
struct TYPE_3__ {scalar_t__ shi2_max_uses; scalar_t__ shi2_current_uses; int /*<<< orphan*/  shi2_remark; int /*<<< orphan*/  shi2_path; int /*<<< orphan*/  shi2_netname; } ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  TYPE_1__* PSHARE_INFO_2 ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int INT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ NERR_Success ; 
 int /*<<< orphan*/  NetApiBufferFree (TYPE_1__*) ; 
 scalar_t__ NetShareGetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintMessageString (int) ; 
 int /*<<< orphan*/  PrintPaddedMessageString (int,int) ; 
 int /*<<< orphan*/  StdOut ; 

NET_API_STATUS
DisplayShare(
    PWSTR pShareName)
{
    PSHARE_INFO_2 pBuffer = NULL;
    INT nPaddedLength = 22;
    NET_API_STATUS Status;

    Status = NetShareGetInfo(NULL,
                             pShareName,
                             2,
                             (LPBYTE*)&pBuffer);
    if (Status != NERR_Success)
        return Status;

    PrintPaddedMessageString(4731, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", pBuffer->shi2_netname);

    PrintPaddedMessageString(4339, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", pBuffer->shi2_path);

    PrintPaddedMessageString(4334, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", pBuffer->shi2_remark);

    PrintPaddedMessageString(4735, nPaddedLength);
    if (pBuffer->shi2_max_uses == (DWORD)-1)
        PrintMessageString(4736);
    else
        ConPrintf(StdOut, L"%lu", pBuffer->shi2_max_uses);
    ConPrintf(StdOut, L"\n");

    PrintPaddedMessageString(4737, nPaddedLength);
    if (pBuffer->shi2_current_uses > 0)
        ConPrintf(StdOut, L"%lu", pBuffer->shi2_current_uses);
    ConPrintf(StdOut, L"\n");

    NetApiBufferFree(pBuffer);

    return NERR_Success;
}