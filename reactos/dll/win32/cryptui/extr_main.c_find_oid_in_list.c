#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ psz; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {scalar_t__ lParam; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ PCCRYPT_OID_INFO ;
typedef  TYPE_1__ LVFINDINFOW ;
typedef  TYPE_2__ LVFINDINFOA ;
typedef  scalar_t__ LPCSTR ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_ENHKEY_USAGE_OID_GROUP_ID ; 
 int /*<<< orphan*/  CRYPT_OID_INFO_OID_KEY ; 
 scalar_t__ CryptFindOIDInfo (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LVFI_PARAM ; 
 int /*<<< orphan*/  LVFI_STRING ; 
 int /*<<< orphan*/  LVM_FINDITEMA ; 
 int /*<<< orphan*/  LVM_FINDITEMW ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static LONG_PTR find_oid_in_list(HWND lv, LPCSTR oid)
{
    PCCRYPT_OID_INFO oidInfo = CryptFindOIDInfo(CRYPT_OID_INFO_OID_KEY,
     (void *)oid, CRYPT_ENHKEY_USAGE_OID_GROUP_ID);
    LONG_PTR ret;

    if (oidInfo)
    {
        LVFINDINFOW findInfo;

        findInfo.flags = LVFI_PARAM;
        findInfo.lParam = (LPARAM)oidInfo;
        ret = SendMessageW(lv, LVM_FINDITEMW, -1, (LPARAM)&findInfo);
    }
    else
    {
        LVFINDINFOA findInfo;

        findInfo.flags = LVFI_STRING;
        findInfo.psz = oid;
        ret = SendMessageW(lv, LVM_FINDITEMA, -1, (LPARAM)&findInfo);
    }
    return ret;
}