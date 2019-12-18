#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_PUBKEY ;
typedef  int /*<<< orphan*/  X509_ALGOR ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_4__ {int length; scalar_t__ type; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  TYPE_1__ ASN1_INTEGER ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 long ASN1_INTEGER_get (TYPE_1__*) ; 
 int /*<<< orphan*/  ASN1_TIME_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ BIO_puts (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ERR_pop_to_mark () ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_set_mark () ; 
 int /*<<< orphan*/  EVP_PKEY_print_public (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 scalar_t__ V_ASN1_NEG_INTEGER ; 
 int /*<<< orphan*/  X509V3_extensions_print (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned long,int) ; 
 unsigned long X509_FLAG_COMPAT ; 
 unsigned long X509_FLAG_NO_AUX ; 
 unsigned long X509_FLAG_NO_EXTENSIONS ; 
 unsigned long X509_FLAG_NO_HEADER ; 
 unsigned long X509_FLAG_NO_IDS ; 
 unsigned long X509_FLAG_NO_ISSUER ; 
 unsigned long X509_FLAG_NO_PUBKEY ; 
 unsigned long X509_FLAG_NO_SERIAL ; 
 unsigned long X509_FLAG_NO_SIGDUMP ; 
 unsigned long X509_FLAG_NO_SIGNAME ; 
 unsigned long X509_FLAG_NO_SUBJECT ; 
 unsigned long X509_FLAG_NO_VALIDITY ; 
 unsigned long X509_FLAG_NO_VERSION ; 
 scalar_t__ X509_NAME_print_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  X509_PUBKEY_get0_param (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_aux_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get0_extensions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get0_notAfter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get0_notBefore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get0_signature (int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get0_tbs_sigalg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get0_uids (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ * X509_get_X509_PUBKEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_issuer_name (int /*<<< orphan*/ *) ; 
 TYPE_1__* X509_get_serialNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 
 long X509_get_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_signature_dump (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ X509_signature_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 unsigned long XN_FLAG_SEP_MASK ; 
 unsigned long XN_FLAG_SEP_MULTILINE ; 
 scalar_t__ i2a_ASN1_OBJECT (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int X509_print_ex(BIO *bp, X509 *x, unsigned long nmflags,
                  unsigned long cflag)
{
    long l;
    int ret = 0, i;
    char *m = NULL, mlch = ' ';
    int nmindent = 0;
    ASN1_INTEGER *bs;
    EVP_PKEY *pkey = NULL;
    const char *neg;

    if ((nmflags & XN_FLAG_SEP_MASK) == XN_FLAG_SEP_MULTILINE) {
        mlch = '\n';
        nmindent = 12;
    }

    if (nmflags == X509_FLAG_COMPAT)
        nmindent = 16;

    if (!(cflag & X509_FLAG_NO_HEADER)) {
        if (BIO_write(bp, "Certificate:\n", 13) <= 0)
            goto err;
        if (BIO_write(bp, "    Data:\n", 10) <= 0)
            goto err;
    }
    if (!(cflag & X509_FLAG_NO_VERSION)) {
        l = X509_get_version(x);
        if (l >= 0 && l <= 2) {
            if (BIO_printf(bp, "%8sVersion: %ld (0x%lx)\n", "", l + 1, (unsigned long)l) <= 0)
                goto err;
        } else {
            if (BIO_printf(bp, "%8sVersion: Unknown (%ld)\n", "", l) <= 0)
                goto err;
        }
    }
    if (!(cflag & X509_FLAG_NO_SERIAL)) {

        if (BIO_write(bp, "        Serial Number:", 22) <= 0)
            goto err;

        bs = X509_get_serialNumber(x);
        if (bs->length <= (int)sizeof(long)) {
                ERR_set_mark();
                l = ASN1_INTEGER_get(bs);
                ERR_pop_to_mark();
        } else {
            l = -1;
        }
        if (l != -1) {
            unsigned long ul;
            if (bs->type == V_ASN1_NEG_INTEGER) {
                ul = 0 - (unsigned long)l;
                neg = "-";
            } else {
                ul = l;
                neg = "";
            }
            if (BIO_printf(bp, " %s%lu (%s0x%lx)\n", neg, ul, neg, ul) <= 0)
                goto err;
        } else {
            neg = (bs->type == V_ASN1_NEG_INTEGER) ? " (Negative)" : "";
            if (BIO_printf(bp, "\n%12s%s", "", neg) <= 0)
                goto err;

            for (i = 0; i < bs->length; i++) {
                if (BIO_printf(bp, "%02x%c", bs->data[i],
                               ((i + 1 == bs->length) ? '\n' : ':')) <= 0)
                    goto err;
            }
        }

    }

    if (!(cflag & X509_FLAG_NO_SIGNAME)) {
        const X509_ALGOR *tsig_alg = X509_get0_tbs_sigalg(x);

        if (BIO_puts(bp, "    ") <= 0)
            goto err;
        if (X509_signature_print(bp, tsig_alg, NULL) <= 0)
            goto err;
    }

    if (!(cflag & X509_FLAG_NO_ISSUER)) {
        if (BIO_printf(bp, "        Issuer:%c", mlch) <= 0)
            goto err;
        if (X509_NAME_print_ex(bp, X509_get_issuer_name(x), nmindent, nmflags)
            < 0)
            goto err;
        if (BIO_write(bp, "\n", 1) <= 0)
            goto err;
    }
    if (!(cflag & X509_FLAG_NO_VALIDITY)) {
        if (BIO_write(bp, "        Validity\n", 17) <= 0)
            goto err;
        if (BIO_write(bp, "            Not Before: ", 24) <= 0)
            goto err;
        if (!ASN1_TIME_print(bp, X509_get0_notBefore(x)))
            goto err;
        if (BIO_write(bp, "\n            Not After : ", 25) <= 0)
            goto err;
        if (!ASN1_TIME_print(bp, X509_get0_notAfter(x)))
            goto err;
        if (BIO_write(bp, "\n", 1) <= 0)
            goto err;
    }
    if (!(cflag & X509_FLAG_NO_SUBJECT)) {
        if (BIO_printf(bp, "        Subject:%c", mlch) <= 0)
            goto err;
        if (X509_NAME_print_ex
            (bp, X509_get_subject_name(x), nmindent, nmflags) < 0)
            goto err;
        if (BIO_write(bp, "\n", 1) <= 0)
            goto err;
    }
    if (!(cflag & X509_FLAG_NO_PUBKEY)) {
        X509_PUBKEY *xpkey = X509_get_X509_PUBKEY(x);
        ASN1_OBJECT *xpoid;
        X509_PUBKEY_get0_param(&xpoid, NULL, NULL, NULL, xpkey);
        if (BIO_write(bp, "        Subject Public Key Info:\n", 33) <= 0)
            goto err;
        if (BIO_printf(bp, "%12sPublic Key Algorithm: ", "") <= 0)
            goto err;
        if (i2a_ASN1_OBJECT(bp, xpoid) <= 0)
            goto err;
        if (BIO_puts(bp, "\n") <= 0)
            goto err;

        pkey = X509_get0_pubkey(x);
        if (pkey == NULL) {
            BIO_printf(bp, "%12sUnable to load Public Key\n", "");
            ERR_print_errors(bp);
        } else {
            EVP_PKEY_print_public(bp, pkey, 16, NULL);
        }
    }

    if (!(cflag & X509_FLAG_NO_IDS)) {
        const ASN1_BIT_STRING *iuid, *suid;
        X509_get0_uids(x, &iuid, &suid);
        if (iuid != NULL) {
            if (BIO_printf(bp, "%8sIssuer Unique ID: ", "") <= 0)
                goto err;
            if (!X509_signature_dump(bp, iuid, 12))
                goto err;
        }
        if (suid != NULL) {
            if (BIO_printf(bp, "%8sSubject Unique ID: ", "") <= 0)
                goto err;
            if (!X509_signature_dump(bp, suid, 12))
                goto err;
        }
    }

    if (!(cflag & X509_FLAG_NO_EXTENSIONS))
        X509V3_extensions_print(bp, "X509v3 extensions",
                                X509_get0_extensions(x), cflag, 8);

    if (!(cflag & X509_FLAG_NO_SIGDUMP)) {
        const X509_ALGOR *sig_alg;
        const ASN1_BIT_STRING *sig;
        X509_get0_signature(&sig, &sig_alg, x);
        if (X509_signature_print(bp, sig_alg, sig) <= 0)
            goto err;
    }
    if (!(cflag & X509_FLAG_NO_AUX)) {
        if (!X509_aux_print(bp, x, 0))
            goto err;
    }
    ret = 1;
 err:
    OPENSSL_free(m);
    return ret;
}