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
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/ * PEM_read_bio_X509_CRL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * glue2bio (char const**,char**) ; 

__attribute__((used)) static X509_CRL *CRL_from_strings(const char **pem)
{
    char *p;
    BIO *b = glue2bio(pem, &p);
    X509_CRL *crl = PEM_read_bio_X509_CRL(b, NULL, NULL, NULL);

    OPENSSL_free(p);
    BIO_free(b);
    return crl;
}