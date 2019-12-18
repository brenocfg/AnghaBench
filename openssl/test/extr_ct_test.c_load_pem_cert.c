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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char*,char*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/ * PEM_read_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* test_mk_file_path (char const*,char const*) ; 

__attribute__((used)) static X509 *load_pem_cert(const char *dir, const char *file)
{
    X509 *cert = NULL;
    char *file_path = test_mk_file_path(dir, file);

    if (file_path != NULL) {
        BIO *cert_io = BIO_new_file(file_path, "r");

        if (cert_io != NULL)
            cert = PEM_read_bio_X509(cert_io, NULL, NULL, NULL);
        BIO_free(cert_io);
    }

    OPENSSL_free(file_path);
    return cert;
}