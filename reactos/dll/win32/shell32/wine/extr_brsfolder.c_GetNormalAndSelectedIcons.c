#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* iSelectedImage; void* iImage; } ;
typedef  TYPE_1__* LPTVITEMW ;
typedef  int /*<<< orphan*/ * LPITEMIDLIST ;
typedef  int DWORD ;

/* Variables and functions */
 void* GetIcon (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ILFree (int /*<<< orphan*/ *) ; 
 int SHGFI_OPENICON ; 
 int SHGFI_PIDL ; 
 int SHGFI_SMALLICON ; 
 int SHGFI_SYSICONINDEX ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * _ILCreateDesktop () ; 

__attribute__((used)) static void GetNormalAndSelectedIcons(LPITEMIDLIST lpifq, LPTVITEMW lpTV_ITEM)
{
    LPITEMIDLIST pidlDesktop = NULL;
    DWORD flags;

    TRACE("%p %p\n",lpifq, lpTV_ITEM);

    if (!lpifq)
    {
        pidlDesktop = _ILCreateDesktop();
        lpifq = pidlDesktop;
    }

    flags = SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON;
    lpTV_ITEM->iImage = GetIcon( lpifq, flags );

    flags = SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_OPENICON;
    lpTV_ITEM->iSelectedImage = GetIcon( lpifq, flags );

    if (pidlDesktop)
        ILFree( pidlDesktop );
}