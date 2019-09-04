#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
struct cce_user {int* name; unsigned int value; unsigned int mask; int /*<<< orphan*/  notdone; int /*<<< orphan*/  done; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  iSubItem; int /*<<< orphan*/  iItem; int /*<<< orphan*/  pt; } ;
struct TYPE_5__ {int code; int /*<<< orphan*/  idFrom; } ;
struct TYPE_4__ {int iSubItem; int /*<<< orphan*/  ptAction; } ;
typedef  TYPE_1__ NMITEMACTIVATE ;
typedef  TYPE_2__ NMHDR ;
typedef  TYPE_3__ LVHITTESTINFO ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSelectedProcessId () ; 
 int /*<<< orphan*/  IDC_DEBUG_CHANNELS_LIST ; 
 int /*<<< orphan*/  LVM_SUBITEMHITTEST ; 
 int /*<<< orphan*/  ListView_GetItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ListView_SetItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
#define  NM_CLICK 128 
 int /*<<< orphan*/  OpenProcess (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PROCESS_VM_OPERATION ; 
 int PROCESS_VM_READ ; 
 int PROCESS_VM_WRITE ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  change_channel_CB ; 
 int /*<<< orphan*/  enum_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cce_user*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void DebugChannels_OnNotify(HWND hDlg, LPARAM lParam)
{
    NMHDR*  nmh = (NMHDR*)lParam;

    switch (nmh->code)
    {
    case NM_CLICK:
        if (nmh->idFrom == IDC_DEBUG_CHANNELS_LIST)
        {
            LVHITTESTINFO    lhti;
            HWND             hChannelLV;
            HANDLE           hProcess;
            NMITEMACTIVATE*  nmia = (NMITEMACTIVATE*)lParam;

            hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, GetSelectedProcessId());
            if (!hProcess) return; /* FIXME message box */
            lhti.pt = nmia->ptAction;
            hChannelLV = GetDlgItem(hDlg, IDC_DEBUG_CHANNELS_LIST);
            SendMessageW(hChannelLV, LVM_SUBITEMHITTEST, 0, (LPARAM)&lhti);
            if (nmia->iSubItem >= 1 && nmia->iSubItem <= 4)
            {
                WCHAR            val[2];
                WCHAR            name[32];
                unsigned         bitmask = 1 << (lhti.iSubItem - 1);
                struct cce_user  user;

                ListView_GetItemText(hChannelLV, lhti.iItem, 0, name, sizeof(name) / sizeof(name[0]));
                ListView_GetItemText(hChannelLV, lhti.iItem, lhti.iSubItem, val, sizeof(val) / sizeof(val[0]));
                user.name = name;
                user.value = (val[0] == L'x') ? 0 : bitmask;
                user.mask = bitmask;
                user.done = user.notdone = 0;
                enum_channel(hProcess, change_channel_CB, &user, FALSE);
                if (user.done)
                {
                    val[0] ^= (L'x' ^ L' ');
                    ListView_SetItemText(hChannelLV, lhti.iItem, lhti.iSubItem, val);
                }
                if (user.notdone)
                    printf("Some channel instance weren't correctly set\n");
            }
            CloseHandle(hProcess);
        }
        break;
    }
}