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
typedef  int /*<<< orphan*/  lvi ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {int mask; scalar_t__ iImage; scalar_t__ state; int /*<<< orphan*/  pszText; } ;
struct TYPE_6__ {int /*<<< orphan*/  lgrpi1_comment; int /*<<< orphan*/  lgrpi1_name; } ;
typedef  TYPE_1__* PLOCALGROUP_INFO_1 ;
typedef  int /*<<< orphan*/  NET_API_STATUS ;
typedef  TYPE_2__ LV_ITEM ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 int LVIF_IMAGE ; 
 int LVIF_STATE ; 
 int LVIF_TEXT ; 
 int /*<<< orphan*/  ListView_InsertItem (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ListView_SetItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NERR_Success ; 
 int /*<<< orphan*/  NetApiBufferFree (TYPE_1__*) ; 
 int /*<<< orphan*/  NetLocalGroupEnum (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,size_t*,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 

__attribute__((used)) static VOID
UpdateGroupsList(HWND hwndListView)
{
    NET_API_STATUS netStatus;
    PLOCALGROUP_INFO_1 pBuffer;
    DWORD entriesread;
    DWORD totalentries;
    DWORD_PTR resume_handle = 0;
    DWORD i;
    LV_ITEM lvi;
    INT iItem;

    for (;;)
    {
        netStatus = NetLocalGroupEnum(NULL, 1, (LPBYTE*)&pBuffer,
                                      1024, &entriesread,
                                      &totalentries, &resume_handle);
        if (netStatus != NERR_Success && netStatus != ERROR_MORE_DATA)
            break;

        for (i = 0; i < entriesread; i++)
        {
           memset(&lvi, 0x00, sizeof(lvi));
           lvi.mask = LVIF_TEXT | LVIF_STATE | LVIF_IMAGE;
           lvi.pszText = pBuffer[i].lgrpi1_name;
           lvi.state = 0;
           lvi.iImage = 0;
           iItem = ListView_InsertItem(hwndListView, &lvi);

           ListView_SetItemText(hwndListView, iItem, 1,
                                pBuffer[i].lgrpi1_comment);
        }

        NetApiBufferFree(pBuffer);

        /* No more data left */
        if (netStatus != ERROR_MORE_DATA)
            break;
    }

}