#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_15__ {int /*<<< orphan*/ * TargetPath; } ;
struct TYPE_14__ {scalar_t__ attributes; int /*<<< orphan*/  installed; int /*<<< orphan*/  manifest; scalar_t__ application; scalar_t__ feature; } ;
struct TYPE_13__ {int /*<<< orphan*/  KeyPath; TYPE_4__* assembly; } ;
struct TYPE_12__ {void* Action; } ;
struct TYPE_11__ {int /*<<< orphan*/ ** cache_net; int /*<<< orphan*/ * cache_sxs; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  TYPE_2__ MSIFEATURE ;
typedef  TYPE_3__ MSICOMPONENT ;
typedef  TYPE_4__ MSIASSEMBLY ;
typedef  int /*<<< orphan*/  IAssemblyCache ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ IAssemblyCache_InstallAssembly (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 void* INSTALLSTATE_LOCAL ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 size_t get_clr_version (int /*<<< orphan*/  const*) ; 
 TYPE_2__* msi_get_loaded_feature (TYPE_1__*,scalar_t__) ; 
 TYPE_7__* msi_get_loaded_file (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ msidbAssemblyAttributesWin32 ; 

UINT msi_install_assembly( MSIPACKAGE *package, MSICOMPONENT *comp )
{
    HRESULT hr;
    const WCHAR *manifest;
    IAssemblyCache *cache;
    MSIASSEMBLY *assembly = comp->assembly;
    MSIFEATURE *feature = NULL;

    if (comp->assembly->feature)
        feature = msi_get_loaded_feature( package, comp->assembly->feature );

    if (assembly->application)
    {
        if (feature) feature->Action = INSTALLSTATE_LOCAL;
        return ERROR_SUCCESS;
    }
    if (assembly->attributes == msidbAssemblyAttributesWin32)
    {
        if (!assembly->manifest)
        {
            WARN("no manifest\n");
            return ERROR_FUNCTION_FAILED;
        }
        manifest = msi_get_loaded_file( package, assembly->manifest )->TargetPath;
        cache = package->cache_sxs;
    }
    else
    {
        manifest = msi_get_loaded_file( package, comp->KeyPath )->TargetPath;
        cache = package->cache_net[get_clr_version( manifest )];
        if (!cache) return ERROR_SUCCESS;
    }
    TRACE("installing assembly %s\n", debugstr_w(manifest));

    hr = IAssemblyCache_InstallAssembly( cache, 0, manifest, NULL );
    if (hr != S_OK)
    {
        ERR("Failed to install assembly %s (0x%08x)\n", debugstr_w(manifest), hr);
        return ERROR_FUNCTION_FAILED;
    }
    if (feature) feature->Action = INSTALLSTATE_LOCAL;
    assembly->installed = TRUE;
    return ERROR_SUCCESS;
}