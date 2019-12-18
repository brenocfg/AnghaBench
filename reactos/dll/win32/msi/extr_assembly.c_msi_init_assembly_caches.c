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
struct TYPE_3__ {int /*<<< orphan*/ * cache_net; int /*<<< orphan*/  cache_sxs; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t CLR_VERSION_V10 ; 
 size_t CLR_VERSION_V11 ; 
 size_t CLR_VERSION_V20 ; 
 size_t CLR_VERSION_V40 ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  init_function_pointers () ; 
 int /*<<< orphan*/  pCreateAssemblyCacheNet10 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCreateAssemblyCacheNet11 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCreateAssemblyCacheNet20 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCreateAssemblyCacheNet40 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pCreateAssemblyCacheSxs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOL msi_init_assembly_caches( MSIPACKAGE *package )
{
    if (!init_function_pointers()) return FALSE;
    if (pCreateAssemblyCacheSxs( &package->cache_sxs, 0 ) != S_OK) return FALSE;
    if (pCreateAssemblyCacheNet10) pCreateAssemblyCacheNet10( &package->cache_net[CLR_VERSION_V10], 0 );
    if (pCreateAssemblyCacheNet11) pCreateAssemblyCacheNet11( &package->cache_net[CLR_VERSION_V11], 0 );
    if (pCreateAssemblyCacheNet20) pCreateAssemblyCacheNet20( &package->cache_net[CLR_VERSION_V20], 0 );
    if (pCreateAssemblyCacheNet40) pCreateAssemblyCacheNet40( &package->cache_net[CLR_VERSION_V40], 0 );
    return TRUE;
}