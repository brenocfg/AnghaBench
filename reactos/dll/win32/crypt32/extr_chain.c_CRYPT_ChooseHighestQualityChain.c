#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t cLowerQualityChainContext; scalar_t__* rgpLowerQualityChainContext; } ;
struct TYPE_7__ {TYPE_1__ context; } ;
typedef  scalar_t__ PCCERT_CHAIN_CONTEXT ;
typedef  size_t DWORD ;
typedef  TYPE_2__ CertificateChain ;

/* Variables and functions */
 scalar_t__ CRYPT_ChainQuality (TYPE_2__*) ; 

__attribute__((used)) static CertificateChain *CRYPT_ChooseHighestQualityChain(
 CertificateChain *chain)
{
    DWORD i;

    /* There are always only two chains being considered:  chain, and an
     * alternate at chain->rgpLowerQualityChainContext[i].  If the alternate
     * has a higher quality than chain, the alternate gets assigned the lower
     * quality contexts, with chain taking the alternate's place among the
     * lower quality contexts.
     */
    for (i = 0; i < chain->context.cLowerQualityChainContext; i++)
    {
        CertificateChain *alternate =
         (CertificateChain*)chain->context.rgpLowerQualityChainContext[i];

        if (CRYPT_ChainQuality(alternate) > CRYPT_ChainQuality(chain))
        {
            alternate->context.cLowerQualityChainContext =
             chain->context.cLowerQualityChainContext;
            alternate->context.rgpLowerQualityChainContext =
             chain->context.rgpLowerQualityChainContext;
            alternate->context.rgpLowerQualityChainContext[i] =
             (PCCERT_CHAIN_CONTEXT)chain;
            chain->context.cLowerQualityChainContext = 0;
            chain->context.rgpLowerQualityChainContext = NULL;
            chain = alternate;
        }
    }
    return chain;
}