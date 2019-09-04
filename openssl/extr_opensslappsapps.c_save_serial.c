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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  BIGNUM ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char*,char*) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int BIO_snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/ * BN_to_ASN1_INTEGER (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int BSIZE ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  i2a_ASN1_INTEGER (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

int save_serial(const char *serialfile, const char *suffix, const BIGNUM *serial,
                ASN1_INTEGER **retai)
{
    char buf[1][BSIZE];
    BIO *out = NULL;
    int ret = 0;
    ASN1_INTEGER *ai = NULL;
    int j;

    if (suffix == NULL)
        j = strlen(serialfile);
    else
        j = strlen(serialfile) + strlen(suffix) + 1;
    if (j >= BSIZE) {
        BIO_printf(bio_err, "file name too long\n");
        goto err;
    }

    if (suffix == NULL)
        OPENSSL_strlcpy(buf[0], serialfile, BSIZE);
    else {
#ifndef OPENSSL_SYS_VMS
        j = BIO_snprintf(buf[0], sizeof(buf[0]), "%s.%s", serialfile, suffix);
#else
        j = BIO_snprintf(buf[0], sizeof(buf[0]), "%s-%s", serialfile, suffix);
#endif
    }
    out = BIO_new_file(buf[0], "w");
    if (out == NULL) {
        ERR_print_errors(bio_err);
        goto err;
    }

    if ((ai = BN_to_ASN1_INTEGER(serial, NULL)) == NULL) {
        BIO_printf(bio_err, "error converting serial to ASN.1 format\n");
        goto err;
    }
    i2a_ASN1_INTEGER(out, ai);
    BIO_puts(out, "\n");
    ret = 1;
    if (retai) {
        *retai = ai;
        ai = NULL;
    }
 err:
    BIO_free_all(out);
    ASN1_INTEGER_free(ai);
    return ret;
}