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
typedef  int RD_BOOL ;
typedef  int /*<<< orphan*/  PCCERT_CONTEXT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CERT_STORE_SIGNATURE_FLAG ; 
 int /*<<< orphan*/  CertVerifySubjectCertificateContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 

RD_BOOL rdssl_certs_ok(PCCERT_CONTEXT server_cert, PCCERT_CONTEXT cacert)
{
    /* FIXME should we check for expired certificates??? */
    DWORD dwFlags = CERT_STORE_SIGNATURE_FLAG; /* CERT_STORE_TIME_VALIDITY_FLAG */
    BOOL ret = CertVerifySubjectCertificateContext(server_cert,
                                                   cacert,
                                                   &dwFlags);
    if (!ret)
    {
        error("CertVerifySubjectCertificateContext call failed with %lx\n", GetLastError());
    }
    if (dwFlags)
    {
        error("CertVerifySubjectCertificateContext check failed %lx\n", dwFlags);
    }
    return (dwFlags == 0);
}