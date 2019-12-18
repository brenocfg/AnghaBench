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
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetSelectedProcessId () ; 
 int /*<<< orphan*/  ListView_DeleteAllItems (scalar_t__) ; 
 int /*<<< orphan*/  OpenProcess (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PROCESS_VM_OPERATION ; 
 int PROCESS_VM_READ ; 
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SETREDRAW ; 
 int /*<<< orphan*/  enum_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_channel_CB ; 

__attribute__((used)) static void DebugChannels_FillList(HWND hChannelLV)
{
    HANDLE  hProcess;

    (void)ListView_DeleteAllItems(hChannelLV);

    hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ, FALSE, GetSelectedProcessId());
    if (!hProcess) return; /* FIXME messagebox */
    SendMessageW(hChannelLV, WM_SETREDRAW, FALSE, 0);
    enum_channel(hProcess, list_channel_CB, (void*)hChannelLV, TRUE);
    SendMessageW(hChannelLV, WM_SETREDRAW, TRUE, 0);
    CloseHandle(hProcess);
}