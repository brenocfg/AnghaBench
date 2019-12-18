#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct name {void* version; void* type; void* token; void* arch; scalar_t__* name; } ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE_NAME ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  archW ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,unsigned int) ; 
 void* parse_value (char const*,unsigned int*) ; 
 int /*<<< orphan*/  tokenW ; 
 int /*<<< orphan*/  typeW ; 
 int /*<<< orphan*/  versionW ; 

__attribute__((used)) static HRESULT parse_displayname( struct name *name, const WCHAR *displayname )
{
    const WCHAR *p, *q;
    unsigned int len;

    p = q = displayname;
    while (*q && *q != ',') q++;
    len = q - p;
    if (!(name->name = HeapAlloc( GetProcessHeap(), 0, (len + 1) * sizeof(WCHAR) ))) return E_OUTOFMEMORY;
    memcpy( name->name, p, len * sizeof(WCHAR) );
    name->name[len] = 0;
    if (!*q) return S_OK;

    for (;;)
    {
        p = ++q;
        while (*q && *q != '=') q++;
        if (!*q) return E_INVALIDARG;
        len = q - p;
        if (len == ARRAY_SIZE(archW) - 1 && !memcmp( p, archW, len * sizeof(WCHAR) ))
        {
            p = ++q;
            if (!(name->arch = parse_value( p, &len ))) return E_INVALIDARG;
            q += len;
        }
        else if (len == ARRAY_SIZE(tokenW) - 1 && !memcmp( p, tokenW, len * sizeof(WCHAR) ))
        {
            p = ++q;
            if (!(name->token = parse_value( p, &len ))) return E_INVALIDARG;
            q += len;
        }
        else if (len == ARRAY_SIZE(typeW) - 1 && !memcmp( p, typeW, len * sizeof(WCHAR) ))
        {
            p = ++q;
            if (!(name->type = parse_value( p, &len ))) return E_INVALIDARG;
            q += len;
        }
        else if (len == ARRAY_SIZE(versionW) - 1 && !memcmp( p, versionW, len * sizeof(WCHAR) ))
        {
            p = ++q;
            if (!(name->version = parse_value( p, &len ))) return E_INVALIDARG;
            q += len;
        }
        else return HRESULT_FROM_WIN32( ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE_NAME );
        while (*q && *q != ',') q++;
        if (!*q) break;
    }
    return S_OK;
}