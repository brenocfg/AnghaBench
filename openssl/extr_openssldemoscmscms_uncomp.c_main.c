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
typedef  int /*<<< orphan*/  CMS_ContentInfo ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char*,char*) ; 
 int /*<<< orphan*/  CMS_ContentInfo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMS_uncompress (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_load_crypto_strings () ; 
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 int /*<<< orphan*/ * SMIME_read_CMS (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
    BIO *in = NULL, *out = NULL;
    CMS_ContentInfo *cms = NULL;
    int ret = 1;

    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    /* Open compressed content */

    in = BIO_new_file("smcomp.txt", "r");

    if (!in)
        goto err;

    /* Sign content */
    cms = SMIME_read_CMS(in, NULL);

    if (!cms)
        goto err;

    out = BIO_new_file("smuncomp.txt", "w");
    if (!out)
        goto err;

    /* Uncompress S/MIME message */
    if (!CMS_uncompress(cms, out, NULL, 0))
        goto err;

    ret = 0;

 err:

    if (ret) {
        fprintf(stderr, "Error Uncompressing Data\n");
        ERR_print_errors_fp(stderr);
    }

    CMS_ContentInfo_free(cms);
    BIO_free(in);
    BIO_free(out);
    return ret;
}