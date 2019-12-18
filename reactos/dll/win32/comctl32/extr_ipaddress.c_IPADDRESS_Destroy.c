#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Self; TYPE_1__* Part; } ;
struct TYPE_5__ {scalar_t__ OrigProc; int /*<<< orphan*/  EditHwnd; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ IPPART_INFO ;
typedef  TYPE_2__ IPADDRESS_INFO ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_WNDPROC ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 

__attribute__((used)) static LRESULT IPADDRESS_Destroy (IPADDRESS_INFO *infoPtr)
{
    int i;

    TRACE("\n");

    for (i = 0; i < 4; i++) {
	IPPART_INFO* part = &infoPtr->Part[i];
        SetWindowLongPtrW (part->EditHwnd, GWLP_WNDPROC, (DWORD_PTR)part->OrigProc);
    }

    SetWindowLongPtrW (infoPtr->Self, 0, 0);
    heap_free (infoPtr);
    return 0;
}