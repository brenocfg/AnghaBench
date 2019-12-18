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
typedef  int WORD ;
struct TYPE_3__ {int /*<<< orphan*/  string_list; } ;
typedef  int /*<<< orphan*/  TLBString ;
typedef  TYPE_1__ ITypeLibImpl ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SysAllocStringLen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TLB_append_str (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static WORD SLTG_ReadString(const char *ptr, const TLBString **pStr, ITypeLibImpl *lib)
{
    WORD bytelen;
    DWORD len;
    BSTR tmp_str;

    *pStr = NULL;
    bytelen = *(const WORD*)ptr;
    if(bytelen == 0xffff) return 2;

    len = MultiByteToWideChar(CP_ACP, 0, ptr + 2, bytelen, NULL, 0);
    tmp_str = SysAllocStringLen(NULL, len);
    if (tmp_str) {
        MultiByteToWideChar(CP_ACP, 0, ptr + 2, bytelen, tmp_str, len);
        *pStr = TLB_append_str(&lib->string_list, tmp_str);
        SysFreeString(tmp_str);
    }
    return bytelen + 2;
}