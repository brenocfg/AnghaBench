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
struct tlibredirect_data {int name_offset; int name_len; } ;
struct ifacepsredirect_data {int /*<<< orphan*/  tlbid; } ;
typedef  int /*<<< orphan*/  data ;
typedef  scalar_t__ WCHAR ;
struct TYPE_3__ {int cbSize; scalar_t__ lpSectionBase; scalar_t__ lpData; } ;
typedef  int /*<<< orphan*/ * REFIID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_1__ ACTCTX_SECTION_KEYED_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVATION_CONTEXT_SECTION_COM_INTERFACE_REDIRECTION ; 
 int /*<<< orphan*/  ACTIVATION_CONTEXT_SECTION_COM_TYPE_LIBRARY_REDIRECTION ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FindActCtxSectionGuid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static BOOL actctx_get_typelib_module(REFIID iid, WCHAR *module, DWORD len)
{
    struct ifacepsredirect_data *iface;
    struct tlibredirect_data *tlib;
    ACTCTX_SECTION_KEYED_DATA data;
    WCHAR *ptrW;

    data.cbSize = sizeof(data);
    if (!FindActCtxSectionGuid(0, NULL, ACTIVATION_CONTEXT_SECTION_COM_INTERFACE_REDIRECTION,
            iid, &data))
        return FALSE;

    iface = (struct ifacepsredirect_data *)data.lpData;
    if (!FindActCtxSectionGuid(0, NULL, ACTIVATION_CONTEXT_SECTION_COM_TYPE_LIBRARY_REDIRECTION,
            &iface->tlbid, &data))
        return FALSE;

    tlib = (struct tlibredirect_data *)data.lpData;
    ptrW = (WCHAR *)((BYTE *)data.lpSectionBase + tlib->name_offset);

    if (tlib->name_len/sizeof(WCHAR) >= len)
    {
        ERR("need larger module buffer, %u\n", tlib->name_len);
        return FALSE;
    }

    memcpy(module, ptrW, tlib->name_len);
    module[tlib->name_len/sizeof(WCHAR)] = 0;
    return TRUE;
}