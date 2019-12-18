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
struct TYPE_4__ {int dwSize; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  hwndParent; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ CRYPTUI_CERT_MGR_STRUCT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CryptUIDlgCertMgr (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 

__attribute__((used)) static BOOL display_cert_manager(HWND parent, DWORD flags)
{
    CRYPTUI_CERT_MGR_STRUCT dlg;

    TRACE("(%p, 0x%x)\n", parent, flags);

    ZeroMemory(&dlg, sizeof(CRYPTUI_CERT_MGR_STRUCT));
    dlg.dwSize = sizeof(CRYPTUI_CERT_MGR_STRUCT);
    dlg.hwndParent = parent;
    dlg.dwFlags = flags;

    return CryptUIDlgCertMgr(&dlg);
}