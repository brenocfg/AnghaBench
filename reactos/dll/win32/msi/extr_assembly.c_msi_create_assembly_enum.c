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
typedef  int /*<<< orphan*/  const WCHAR ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  int /*<<< orphan*/  IAssemblyName ;
typedef  int /*<<< orphan*/  IAssemblyEnum ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_CACHE_GAC ; 
 int /*<<< orphan*/  CANOF_PARSE_DISPLAY_NAME ; 
 scalar_t__ E_NOT_SUFFICIENT_BUFFER ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IAssemblyName_GetName (int /*<<< orphan*/ *,int*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  IAssemblyName_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/  const*) ; 
 scalar_t__ pCreateAssemblyEnum (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pCreateAssemblyNameObject (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

IAssemblyEnum *msi_create_assembly_enum( MSIPACKAGE *package, const WCHAR *displayname )
{
    HRESULT hr;
    IAssemblyName *name;
    IAssemblyEnum *ret;
    WCHAR *str;
    UINT len = 0;

    if (!pCreateAssemblyNameObject || !pCreateAssemblyEnum) return NULL;

    hr = pCreateAssemblyNameObject( &name, displayname, CANOF_PARSE_DISPLAY_NAME, NULL );
    if (FAILED( hr )) return NULL;

    hr = IAssemblyName_GetName( name, &len, NULL );
    if (hr != E_NOT_SUFFICIENT_BUFFER || !(str = msi_alloc( len * sizeof(WCHAR) )))
    {
        IAssemblyName_Release( name );
        return NULL;
    }

    hr = IAssemblyName_GetName( name, &len, str );
    IAssemblyName_Release( name );
    if (FAILED( hr ))
    {
        msi_free( str );
        return NULL;
    }

    hr = pCreateAssemblyNameObject( &name, str, 0, NULL );
    msi_free( str );
    if (FAILED( hr )) return NULL;

    hr = pCreateAssemblyEnum( &ret, NULL, name, ASM_CACHE_GAC, NULL );
    IAssemblyName_Release( name );
    if (FAILED( hr )) return NULL;

    return ret;
}