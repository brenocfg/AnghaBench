#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  chainPara ;
typedef  int /*<<< orphan*/  chainEngineConfig ;
struct TYPE_18__ {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_12__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_17__ {int member_0; TYPE_1__ member_1; } ;
struct TYPE_13__ {int dwErrorStatus; } ;
struct TYPE_16__ {int cChain; TYPE_4__** rgpChain; TYPE_2__ TrustStatus; } ;
struct TYPE_15__ {int cElement; TYPE_3__** rgpElement; } ;
struct TYPE_14__ {int /*<<< orphan*/  pCertContext; } ;
typedef  int /*<<< orphan*/ * PCCERT_CONTEXT ;
typedef  TYPE_5__* PCCERT_CHAIN_CONTEXT ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  scalar_t__ HCERTCHAINENGINE ;
typedef  int DWORD ;
typedef  TYPE_6__ CERT_CHAIN_PARA ;
typedef  TYPE_7__ CERT_CHAIN_ENGINE_CONFIG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_CHAIN_CACHE_ONLY_URL_RETRIEVAL ; 
 int /*<<< orphan*/  CERT_STORE_ADD_NEW ; 
 int /*<<< orphan*/  CERT_SYSTEM_STORE_CURRENT_USER ; 
 int CERT_TRUST_INVALID_BASIC_CONSTRAINTS ; 
 int CERT_TRUST_IS_NOT_TIME_VALID ; 
 int CERT_TRUST_IS_NOT_VALID_FOR_USAGE ; 
 int CERT_TRUST_IS_UNTRUSTED_ROOT ; 
 scalar_t__ CRYPT_CreateChainEngine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 scalar_t__ CertAddCertificateContextToStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CertDuplicateStore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CertEnumCertificatesInStore (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CertFreeCertificateChain (TYPE_5__*) ; 
 int /*<<< orphan*/  CertFreeCertificateChainEngine (scalar_t__) ; 
 int /*<<< orphan*/  CertGetCertificateChain (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__**) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  get_cert_common_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trust_status_to_str (int) ; 

__attribute__((used)) static void check_and_store_certs(HCERTSTORE from, HCERTSTORE to)
{
    DWORD root_count = 0;
    CERT_CHAIN_ENGINE_CONFIG chainEngineConfig =
     { sizeof(chainEngineConfig), 0 };
    HCERTCHAINENGINE engine;

    TRACE("\n");

    CertDuplicateStore(to);
    engine = CRYPT_CreateChainEngine(to, CERT_SYSTEM_STORE_CURRENT_USER, &chainEngineConfig);
    if (engine)
    {
        PCCERT_CONTEXT cert = NULL;

        do {
            cert = CertEnumCertificatesInStore(from, cert);
            if (cert)
            {
                CERT_CHAIN_PARA chainPara = { sizeof(chainPara), { 0 } };
                PCCERT_CHAIN_CONTEXT chain;
                BOOL ret;

                ret = CertGetCertificateChain(engine, cert, NULL, from,
                 &chainPara, CERT_CHAIN_CACHE_ONLY_URL_RETRIEVAL, NULL, &chain);
                if (!ret)
                    TRACE("rejecting %s: %s\n", get_cert_common_name(cert),
                     "chain creation failed");
                else
                {
                    DWORD allowedErrors = CERT_TRUST_IS_UNTRUSTED_ROOT |
                     CERT_TRUST_IS_NOT_VALID_FOR_USAGE |
                     CERT_TRUST_INVALID_BASIC_CONSTRAINTS |
                     CERT_TRUST_IS_NOT_TIME_VALID;

                    /* The certificate chain verification only allows certain
                     * invalid CA certs if they're installed locally:  CA
                     * certs missing the key usage extension, and CA certs
                     * missing the basic constraints extension.  Of course
                     * there's a chicken and egg problem:  we have to accept
                     * them here in order for them to be accepted later.
                     * Expired, locally installed certs are also allowed here,
                     * because we don't know (yet) what date will be checked
                     * for an item signed by one of these certs.
                     * Thus, accept certs with any of the allowed errors.
                     */
                    if (chain->TrustStatus.dwErrorStatus & ~allowedErrors)
                        TRACE("rejecting %s: %s\n", get_cert_common_name(cert),
                         trust_status_to_str(chain->TrustStatus.dwErrorStatus &
                         ~CERT_TRUST_IS_UNTRUSTED_ROOT));
                    else
                    {
                        DWORD i, j;

                        for (i = 0; i < chain->cChain; i++)
                            for (j = 0; j < chain->rgpChain[i]->cElement; j++)
                                if (CertAddCertificateContextToStore(to,
                                 chain->rgpChain[i]->rgpElement[j]->pCertContext,
                                 CERT_STORE_ADD_NEW, NULL))
                                    root_count++;
                    }
                    CertFreeCertificateChain(chain);
                }
            }
        } while (cert);
        CertFreeCertificateChainEngine(engine);
    }
    TRACE("Added %d root certificates\n", root_count);
}