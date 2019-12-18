#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* displayname; char* name; char* procarch; char* culture; } ;
typedef  char* LPWSTR ;
typedef  char* LPCWSTR ;
typedef  TYPE_1__ IAssemblyNameImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FUSION_E_INVALID_NAME ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  culture ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  lstrcmpiW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_culture (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  parse_procarch (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  parse_pubkey (TYPE_1__*,char*) ; 
 char* parse_value (char*,int) ; 
 int /*<<< orphan*/  parse_version (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  procarch ; 
 int /*<<< orphan*/  pubkey ; 
 void* strdupW (char*) ; 
 int /*<<< orphan*/  version ; 
 char* wcschr (char*,char) ; 

__attribute__((used)) static HRESULT parse_display_name(IAssemblyNameImpl *name, LPCWSTR szAssemblyName)
{
    LPWSTR str, save, ptr, ptr2, value;
    HRESULT hr = S_OK;
    BOOL done = FALSE;

    if (!szAssemblyName)
        return S_OK;

    name->displayname = strdupW(szAssemblyName);
    if (!name->displayname)
        return E_OUTOFMEMORY;

    str = strdupW(szAssemblyName);
    save = str;
    if (!str)
    {
        hr = E_OUTOFMEMORY;
        goto done;
    }

    ptr = wcschr(str, ',');
    if (ptr) *ptr = '\0';

    /* no ',' but ' ' only */
    if( !ptr && wcschr(str, ' ') )
    {
        hr = FUSION_E_INVALID_NAME;
        goto done;
    }

    name->name = strdupW(str);
    if (!name->name)
    {
        hr = E_OUTOFMEMORY;
        goto done;
    }

    if (!ptr)
        goto done;

    str = ptr + 1;
    while (!done)
    {
        ptr = wcschr(str, '=');
        if (!ptr)
        {
            hr = FUSION_E_INVALID_NAME;
            goto done;
        }

        *(ptr++) = '\0';
        if (!*ptr)
        {
            hr = FUSION_E_INVALID_NAME;
            goto done;
        }

        if (!(ptr2 = wcschr(ptr, ',')))
        {
            if (!(ptr2 = wcschr(ptr, '\0')))
            {
                hr = FUSION_E_INVALID_NAME;
                goto done;
            }

            done = TRUE;
        }

        *ptr2 = '\0';
        if (!(value = parse_value( ptr, ptr2 - ptr )))
        {
            hr = FUSION_E_INVALID_NAME;
            goto done;
        }
        while (*str == ' ') str++;

        if (!lstrcmpiW(str, version))
            hr = parse_version( name, value );
        else if (!lstrcmpiW(str, culture))
            hr = parse_culture( name, value );
        else if (!lstrcmpiW(str, pubkey))
            hr = parse_pubkey( name, value );
        else if (!lstrcmpiW(str, procarch))
        {
            name->procarch = value;
            value = NULL;

            hr = parse_procarch( name, name->procarch );
        }
        heap_free( value );

        if (FAILED(hr))
            goto done;

        str = ptr2 + 1;
    }

done:
    heap_free(save);
    if (FAILED(hr))
    {
        heap_free(name->displayname);
        heap_free(name->name);
        heap_free(name->culture);
        heap_free(name->procarch);
    }
    return hr;
}