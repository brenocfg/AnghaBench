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
typedef  int /*<<< orphan*/  X509_CRL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CRL_from_strings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/ * PEM_read_bio_X509_CRL (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_CRL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * glue2bio (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  kBasicCRL ; 
 int /*<<< orphan*/  kRevokedCRL ; 

__attribute__((used)) static int test_reuse_crl(void)
{
    X509_CRL *reused_crl = CRL_from_strings(kBasicCRL);
    char *p;
    BIO *b = glue2bio(kRevokedCRL, &p);

    reused_crl = PEM_read_bio_X509_CRL(b, &reused_crl, NULL, NULL);

    OPENSSL_free(p);
    BIO_free(b);
    X509_CRL_free(reused_crl);
    return 1;
}