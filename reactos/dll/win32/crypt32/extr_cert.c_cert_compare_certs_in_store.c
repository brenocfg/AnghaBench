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
typedef  int /*<<< orphan*/ * PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ (* CertCompareFunc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * CertEnumCertificatesInStore (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 

__attribute__((used)) static inline PCCERT_CONTEXT cert_compare_certs_in_store(HCERTSTORE store,
 PCCERT_CONTEXT prev, CertCompareFunc compare, DWORD dwType, DWORD dwFlags,
 const void *pvPara)
{
    BOOL matches = FALSE;
    PCCERT_CONTEXT ret;

    ret = prev;
    do {
        ret = CertEnumCertificatesInStore(store, ret);
        if (ret)
            matches = compare(ret, dwType, dwFlags, pvPara);
    } while (ret != NULL && !matches);
    return ret;
}