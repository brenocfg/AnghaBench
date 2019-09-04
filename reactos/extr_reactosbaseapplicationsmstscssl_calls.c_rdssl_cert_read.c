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
typedef  int /*<<< orphan*/  uint8 ;
typedef  char* uint32 ;
typedef  int /*<<< orphan*/ * PCCERT_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/ * CertCreateCertificateContext (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int PKCS_7_ASN_ENCODING ; 
 int X509_ASN_ENCODING ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,...) ; 

PCCERT_CONTEXT rdssl_cert_read(uint8 * data, uint32 len)
{
    PCCERT_CONTEXT res;
    if (!data || !len)
    {
        error("rdssl_cert_read %p %ld\n", data, len);
        return NULL;
    }
    res = CertCreateCertificateContext(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, data, len);
    if (!res)
    {
        error("CertCreateCertificateContext call failed with %lx\n", GetLastError());
    }
    return res;
}