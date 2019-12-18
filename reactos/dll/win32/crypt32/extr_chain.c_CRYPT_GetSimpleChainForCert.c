#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int cbSize; } ;
typedef  TYPE_1__* PCERT_SIMPLE_CHAIN ;
typedef  int /*<<< orphan*/  PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  LPFILETIME ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CertificateChainEngine ;
typedef  int /*<<< orphan*/  CERT_SIMPLE_CHAIN ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CRYPT_AddCertToSimpleChain (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CRYPT_BuildSimpleChain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CRYPT_CheckSimpleChain (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPT_FreeSimpleChain (TYPE_1__*) ; 
 TYPE_1__* CryptMemAlloc (int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_filetime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL CRYPT_GetSimpleChainForCert(CertificateChainEngine *engine,
 HCERTSTORE world, PCCERT_CONTEXT cert, LPFILETIME pTime, DWORD flags,
 PCERT_SIMPLE_CHAIN *ppChain)
{
    BOOL ret = FALSE;
    PCERT_SIMPLE_CHAIN chain;

    TRACE("(%p, %p, %p, %s)\n", engine, world, cert, debugstr_filetime(pTime));

    chain = CryptMemAlloc(sizeof(CERT_SIMPLE_CHAIN));
    if (chain)
    {
        memset(chain, 0, sizeof(CERT_SIMPLE_CHAIN));
        chain->cbSize = sizeof(CERT_SIMPLE_CHAIN);
        ret = CRYPT_AddCertToSimpleChain(engine, chain, cert, 0);
        if (ret)
        {
            ret = CRYPT_BuildSimpleChain(engine, world, flags, chain);
            if (ret)
                CRYPT_CheckSimpleChain(engine, chain, pTime);
        }
        if (!ret)
        {
            CRYPT_FreeSimpleChain(chain);
            chain = NULL;
        }
        *ppChain = chain;
    }
    return ret;
}