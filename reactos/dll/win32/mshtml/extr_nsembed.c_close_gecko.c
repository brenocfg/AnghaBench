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

/* Variables and functions */
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ cat_mgr ; 
 int /*<<< orphan*/  cs_load_gecko ; 
 int /*<<< orphan*/  init_mutation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsICategoryManager_Release (scalar_t__) ; 
 int /*<<< orphan*/  nsIComponentManager_Release (scalar_t__) ; 
 int /*<<< orphan*/  nsIFile_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIServiceManager_Release (scalar_t__) ; 
 scalar_t__ pCompMgr ; 
 scalar_t__ pServMgr ; 
 int /*<<< orphan*/ * plugin_directory ; 
 int /*<<< orphan*/ * profile_directory ; 
 int /*<<< orphan*/  release_nsio () ; 

void close_gecko(void)
{
    TRACE("()\n");

    release_nsio();
    init_mutation(NULL);

    if(profile_directory) {
        nsIFile_Release(profile_directory);
        profile_directory = NULL;
    }

    if(plugin_directory) {
        nsIFile_Release(plugin_directory);
        plugin_directory = NULL;
    }

    if(pCompMgr)
        nsIComponentManager_Release(pCompMgr);

    if(pServMgr)
        nsIServiceManager_Release(pServMgr);

    if(cat_mgr)
        nsICategoryManager_Release(cat_mgr);

    /* Gecko doesn't really support being unloaded */
    /* if (hXPCOM) FreeLibrary(hXPCOM); */

    DeleteCriticalSection(&cs_load_gecko);
}