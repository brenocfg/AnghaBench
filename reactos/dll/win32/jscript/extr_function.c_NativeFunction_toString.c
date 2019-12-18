#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  native_suffixW ;
typedef  int /*<<< orphan*/  native_prefixW ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  char WCHAR ;
struct TYPE_2__ {char const* name; } ;
typedef  TYPE_1__ NativeFunction ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FunctionInstance ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * jsstr_alloc_buf (scalar_t__,char**) ; 
 int lstrlenW (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static HRESULT NativeFunction_toString(FunctionInstance *func, jsstr_t **ret)
{
    NativeFunction *function = (NativeFunction*)func;
    DWORD name_len;
    jsstr_t *str;
    WCHAR *ptr;

    static const WCHAR native_prefixW[] = {'\n','f','u','n','c','t','i','o','n',' '};
    static const WCHAR native_suffixW[] =
        {'(',')',' ','{','\n',' ',' ',' ',' ','[','n','a','t','i','v','e',' ','c','o','d','e',']','\n','}','\n'};

    name_len = function->name ? lstrlenW(function->name) : 0;
    str = jsstr_alloc_buf(ARRAY_SIZE(native_prefixW) + ARRAY_SIZE(native_suffixW) + name_len, &ptr);
    if(!str)
        return E_OUTOFMEMORY;

    memcpy(ptr, native_prefixW, sizeof(native_prefixW));
    ptr += ARRAY_SIZE(native_prefixW);
    memcpy(ptr, function->name, name_len*sizeof(WCHAR));
    ptr += name_len;
    memcpy(ptr, native_suffixW, sizeof(native_suffixW));

    *ret = str;
    return S_OK;
}