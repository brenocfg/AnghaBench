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
 int /*<<< orphan*/ * ASN1_INTEGER_new () ; 
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ASN1_INTEGER_to_BN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_to_ASN1_INTEGER (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  a2i_ASN1_INTEGER (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  bio_err ; 

__attribute__((used)) static ASN1_INTEGER *next_serial(const char *serialfile)
{
    int ret = 0;
    BIO *in = NULL;
    ASN1_INTEGER *serial = NULL;
    BIGNUM *bn = NULL;

    if ((serial = ASN1_INTEGER_new()) == NULL)
        goto err;

    if ((in = BIO_new_file(serialfile, "r")) == NULL) {
        ERR_clear_error();
        BIO_printf(bio_err, "Warning: could not open file %s for "
                   "reading, using serial number: 1\n", serialfile);
        if (!ASN1_INTEGER_set(serial, 1))
            goto err;
    } else {
        char buf[1024];
        if (!a2i_ASN1_INTEGER(in, serial, buf, sizeof(buf))) {
            BIO_printf(bio_err, "unable to load number from %s\n",
                       serialfile);
            goto err;
        }
        if ((bn = ASN1_INTEGER_to_BN(serial, NULL)) == NULL)
            goto err;
        ASN1_INTEGER_free(serial);
        serial = NULL;
        if (!BN_add_word(bn, 1))
            goto err;
        if ((serial = BN_to_ASN1_INTEGER(bn, NULL)) == NULL)
            goto err;
    }
    ret = 1;

 err:
    if (!ret) {
        ASN1_INTEGER_free(serial);
        serial = NULL;
    }
    BIO_free_all(in);
    BN_free(bn);
    return serial;
}