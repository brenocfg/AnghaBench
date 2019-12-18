#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* (* loadkey ) (void*,void*,size_t) ;} ;
typedef  TYPE_1__ EVP_KEYMGMT ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KEYMGMT_provider (TYPE_1__ const*) ; 
 void* ossl_provider_ctx (int /*<<< orphan*/ ) ; 
 void* stub1 (void*,void*,size_t) ; 

void *evp_keymgmt_loadkey(const EVP_KEYMGMT *keymgmt,
                          void *id, size_t idlen)
{
    void *provctx = ossl_provider_ctx(EVP_KEYMGMT_provider(keymgmt));

    return keymgmt->loadkey(provctx, id, idlen);
}