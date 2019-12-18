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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIFactory ;
typedef  int /*<<< orphan*/  nsIComponentManager ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_nsIContentUtils ; 
 int /*<<< orphan*/  IID_nsIFactory ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_ICONTENTUTILS_CID ; 
 int /*<<< orphan*/ * content_utils ; 
 int /*<<< orphan*/  nsIComponentManager_GetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIContentUtils_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIFactory_CreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIFactory_Release (int /*<<< orphan*/ *) ; 

void init_mutation(nsIComponentManager *component_manager)
{
    nsIFactory *factory;
    nsresult nsres;

    if(!component_manager) {
        if(content_utils) {
            nsIContentUtils_Release(content_utils);
            content_utils = NULL;
        }
        return;
    }

    nsres = nsIComponentManager_GetClassObject(component_manager, &NS_ICONTENTUTILS_CID,
            &IID_nsIFactory, (void**)&factory);
    if(NS_FAILED(nsres)) {
        ERR("Could not create nsIContentUtils service: %08x\n", nsres);
        return;
    }

    nsres = nsIFactory_CreateInstance(factory, NULL, &IID_nsIContentUtils, (void**)&content_utils);
    nsIFactory_Release(factory);
    if(NS_FAILED(nsres))
        ERR("Could not create nsIContentUtils instance: %08x\n", nsres);
}