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
typedef  int /*<<< orphan*/  PKCS12 ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_load_crypto_strings () ; 
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 int /*<<< orphan*/ * PEM_read_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PKCS12_create (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS12_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  i2d_PKCS12_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
    FILE *fp;
    EVP_PKEY *pkey;
    X509 *cert;
    PKCS12 *p12;
    if (argc != 5) {
        fprintf(stderr, "Usage: pkwrite infile password name p12file\n");
        exit(1);
    }
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        exit(1);
    }
    cert = PEM_read_X509(fp, NULL, NULL, NULL);
    rewind(fp);
    pkey = PEM_read_PrivateKey(fp, NULL, NULL, NULL);
    fclose(fp);
    p12 = PKCS12_create(argv[2], argv[3], pkey, cert, NULL, 0, 0, 0, 0, 0);
    if (!p12) {
        fprintf(stderr, "Error creating PKCS#12 structure\n");
        ERR_print_errors_fp(stderr);
        exit(1);
    }
    if ((fp = fopen(argv[4], "wb")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        ERR_print_errors_fp(stderr);
        exit(1);
    }
    i2d_PKCS12_fp(fp, p12);
    PKCS12_free(p12);
    fclose(fp);
    return 0;
}