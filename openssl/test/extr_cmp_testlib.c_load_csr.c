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
typedef  char const X509_REQ ;
typedef  char const BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (char const*) ; 
 char* BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  TEST_ptr (char const*) ; 
 char* d2i_X509_REQ_bio (char const*,int /*<<< orphan*/ *) ; 

X509_REQ *load_csr(const char *file)
{
    X509_REQ *csr = NULL;
    BIO *bio = NULL;

    if (!TEST_ptr(file) || !TEST_ptr(bio = BIO_new_file(file, "rb")))
        return NULL;
    (void)TEST_ptr(csr = d2i_X509_REQ_bio(bio, NULL));
    BIO_free(bio);
    return csr;
}