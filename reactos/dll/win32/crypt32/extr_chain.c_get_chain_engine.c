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
typedef  int /*<<< orphan*/  config ;
struct TYPE_3__ {int member_0; } ;
typedef  scalar_t__ HCERTCHAINENGINE ;
typedef  int /*<<< orphan*/  CertificateChainEngine ;
typedef  TYPE_1__ CERT_CHAIN_ENGINE_CONFIG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_SYSTEM_STORE_CURRENT_USER ; 
 int /*<<< orphan*/  CERT_SYSTEM_STORE_LOCAL_MACHINE ; 
 scalar_t__ CRYPT_CreateChainEngine (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int /*<<< orphan*/  CertFreeCertificateChainEngine (scalar_t__) ; 
 scalar_t__ HCCE_CURRENT_USER ; 
 scalar_t__ HCCE_LOCAL_MACHINE ; 
 int /*<<< orphan*/  InterlockedCompareExchangePointer (void**,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ default_cu_engine ; 
 scalar_t__ default_lm_engine ; 

__attribute__((used)) static CertificateChainEngine *get_chain_engine(HCERTCHAINENGINE handle, BOOL allow_default)
{
    const CERT_CHAIN_ENGINE_CONFIG config = { sizeof(config) };

    if(handle == HCCE_CURRENT_USER) {
        if(!allow_default)
            return NULL;

        if(!default_cu_engine) {
            handle = CRYPT_CreateChainEngine(NULL, CERT_SYSTEM_STORE_CURRENT_USER, &config);
            InterlockedCompareExchangePointer((void**)&default_cu_engine, handle, NULL);
            if(default_cu_engine != handle)
                CertFreeCertificateChainEngine(handle);
        }

        return default_cu_engine;
    }

    if(handle == HCCE_LOCAL_MACHINE) {
        if(!allow_default)
            return NULL;

        if(!default_lm_engine) {
            handle = CRYPT_CreateChainEngine(NULL, CERT_SYSTEM_STORE_LOCAL_MACHINE, &config);
            InterlockedCompareExchangePointer((void**)&default_lm_engine, handle, NULL);
            if(default_lm_engine != handle)
                CertFreeCertificateChainEngine(handle);
        }

        return default_lm_engine;
    }

    return (CertificateChainEngine*)handle;
}