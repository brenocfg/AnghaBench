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
struct TYPE_3__ {int /*<<< orphan*/  hListView; } ;
typedef  TYPE_1__* PMAIN_WND_INFO ;
typedef  scalar_t__ HIMAGELIST ;
typedef  scalar_t__ HICON ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyIcon (scalar_t__) ; 
 int /*<<< orphan*/  GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDI_SM_ICON ; 
 int ILC_COLOR32 ; 
 int ILC_MASK ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 int /*<<< orphan*/  ImageList_AddIcon (scalar_t__,scalar_t__) ; 
 scalar_t__ ImageList_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  LVSIL_NORMAL ; 
 int /*<<< orphan*/  LVSIL_SMALL ; 
 int /*<<< orphan*/  ListView_SetImageList (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ LoadImageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXICON ; 
 int /*<<< orphan*/  SM_CXSMICON ; 
 int /*<<< orphan*/  SM_CYICON ; 
 int /*<<< orphan*/  SM_CYSMICON ; 
 int /*<<< orphan*/  hInstance ; 

__attribute__((used)) static VOID
InitListViewImage(PMAIN_WND_INFO Info)
{
    HICON hSmIconItem, hLgIconItem;
    HIMAGELIST hSmall, hLarge;

    hSmall = ImageList_Create(GetSystemMetrics(SM_CXSMICON),
                              GetSystemMetrics(SM_CYSMICON),
                              ILC_MASK | ILC_COLOR32,
                              1,
                              1);
    if (hSmall)
    {
        hSmIconItem = LoadImageW(hInstance,
                                 MAKEINTRESOURCE(IDI_SM_ICON),
                                 IMAGE_ICON,
                                 16,
                                 16,
                                 0);
        if (hSmIconItem)
        {
            ImageList_AddIcon(hSmall,
                              hSmIconItem);
            (void)ListView_SetImageList(Info->hListView,
                                        hSmall,
                                        LVSIL_SMALL);

            DestroyIcon(hSmIconItem);
        }
    }

    hLarge = ImageList_Create(GetSystemMetrics(SM_CXICON),
                              GetSystemMetrics(SM_CYICON),
                              ILC_MASK | ILC_COLOR32,
                              1,
                              1);
    if (hLarge)
    {
        hLgIconItem = LoadImageW(hInstance,
                                 MAKEINTRESOURCE(IDI_SM_ICON),
                                 IMAGE_ICON,
                                 32,
                                 32,
                                 0);
        if (hLgIconItem)
        {
            ImageList_AddIcon(hLarge,
                              hLgIconItem);
            (void)ListView_SetImageList(Info->hListView,
                                        hLarge,
                                        LVSIL_NORMAL);
            DestroyIcon(hLgIconItem);
        }
    }
}