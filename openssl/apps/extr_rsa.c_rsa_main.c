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
typedef  int /*<<< orphan*/  RSA ;
typedef  int OPTION_CHOICE ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BN_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ ERR_GET_LIB (unsigned long) ; 
 scalar_t__ ERR_GET_REASON (unsigned long) ; 
 scalar_t__ ERR_LIB_RSA ; 
 scalar_t__ ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 unsigned long ERR_peek_error () ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_reason_error_string (unsigned long) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_RSA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_PKEY_set1_RSA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int FORMAT_ASN1 ; 
 int FORMAT_ASN1RSA ; 
 int FORMAT_MSBLOB ; 
 int FORMAT_PEM ; 
 int FORMAT_PEMRSA ; 
 int FORMAT_PVK ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
#define  OPT_CHECK 149 
#define  OPT_CIPHER 148 
#define  OPT_ENGINE 147 
#define  OPT_EOF 146 
#define  OPT_ERR 145 
 int /*<<< orphan*/  OPT_FMT_ANY ; 
#define  OPT_HELP 144 
#define  OPT_IN 143 
#define  OPT_INFORM 142 
#define  OPT_MODULUS 141 
#define  OPT_NOOUT 140 
#define  OPT_OUT 139 
#define  OPT_OUTFORM 138 
#define  OPT_PASSIN 137 
#define  OPT_PASSOUT 136 
#define  OPT_PUBIN 135 
#define  OPT_PUBOUT 134 
#define  OPT_PVK_NONE 133 
#define  OPT_PVK_STRONG 132 
#define  OPT_PVK_WEAK 131 
#define  OPT_RSAPUBKEY_IN 130 
#define  OPT_RSAPUBKEY_OUT 129 
#define  OPT_TEXT 128 
 int PEM_write_bio_RSAPrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int PEM_write_bio_RSAPublicKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PEM_write_bio_RSA_PUBKEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RSA_check_key_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  app_passwd (char*,char*,char**,char**) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * bio_err ; 
 int /*<<< orphan*/ * bio_open_owner (char*,int,int) ; 
 int i2b_PVK_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int i2b_PrivateKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i2b_PublicKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i2d_RSAPrivateKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i2d_RSAPublicKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i2d_RSA_PUBKEY_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * load_key (char*,int,int,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * load_pubkey (char*,int,int,char*,int /*<<< orphan*/ *,char*) ; 
 char* opt_arg () ; 
 int /*<<< orphan*/  opt_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  opt_format (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 int /*<<< orphan*/  opt_unknown () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  release_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsa_options ; 
 int /*<<< orphan*/ * setup_engine (char*,int /*<<< orphan*/ ) ; 

int rsa_main(int argc, char **argv)
{
    ENGINE *e = NULL;
    BIO *out = NULL;
    RSA *rsa = NULL;
    const EVP_CIPHER *enc = NULL;
    char *infile = NULL, *outfile = NULL, *prog;
    char *passin = NULL, *passout = NULL, *passinarg = NULL, *passoutarg = NULL;
    int i, private = 0;
    int informat = FORMAT_PEM, outformat = FORMAT_PEM, text = 0, check = 0;
    int noout = 0, modulus = 0, pubin = 0, pubout = 0, ret = 1;
# if !defined(OPENSSL_NO_DSA) && !defined(OPENSSL_NO_RC4)
    int pvk_encr = 2;
# endif
    OPTION_CHOICE o;

    prog = opt_init(argc, argv, rsa_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(rsa_options);
            ret = 0;
            goto end;
        case OPT_INFORM:
            if (!opt_format(opt_arg(), OPT_FMT_ANY, &informat))
                goto opthelp;
            break;
        case OPT_IN:
            infile = opt_arg();
            break;
        case OPT_OUTFORM:
            if (!opt_format(opt_arg(), OPT_FMT_ANY, &outformat))
                goto opthelp;
            break;
        case OPT_OUT:
            outfile = opt_arg();
            break;
        case OPT_PASSIN:
            passinarg = opt_arg();
            break;
        case OPT_PASSOUT:
            passoutarg = opt_arg();
            break;
        case OPT_ENGINE:
            e = setup_engine(opt_arg(), 0);
            break;
        case OPT_PUBIN:
            pubin = 1;
            break;
        case OPT_PUBOUT:
            pubout = 1;
            break;
        case OPT_RSAPUBKEY_IN:
            pubin = 2;
            break;
        case OPT_RSAPUBKEY_OUT:
            pubout = 2;
            break;
        case OPT_PVK_STRONG:    /* pvk_encr:= 2 */
        case OPT_PVK_WEAK:      /* pvk_encr:= 1 */
        case OPT_PVK_NONE:      /* pvk_encr:= 0 */
# if !defined(OPENSSL_NO_DSA) && !defined(OPENSSL_NO_RC4)
            pvk_encr = (o - OPT_PVK_NONE);
# endif
            break;
        case OPT_NOOUT:
            noout = 1;
            break;
        case OPT_TEXT:
            text = 1;
            break;
        case OPT_MODULUS:
            modulus = 1;
            break;
        case OPT_CHECK:
            check = 1;
            break;
        case OPT_CIPHER:
            if (!opt_cipher(opt_unknown(), &enc))
                goto opthelp;
            break;
        }
    }
    argc = opt_num_rest();
    if (argc != 0)
        goto opthelp;

    private = (text && !pubin) || (!pubout && !noout) ? 1 : 0;

    if (!app_passwd(passinarg, passoutarg, &passin, &passout)) {
        BIO_printf(bio_err, "Error getting passwords\n");
        goto end;
    }
    if (check && pubin) {
        BIO_printf(bio_err, "Only private keys can be checked\n");
        goto end;
    }

    {
        EVP_PKEY *pkey;

        if (pubin) {
            int tmpformat = -1;
            if (pubin == 2) {
                if (informat == FORMAT_PEM)
                    tmpformat = FORMAT_PEMRSA;
                else if (informat == FORMAT_ASN1)
                    tmpformat = FORMAT_ASN1RSA;
            } else {
                tmpformat = informat;
            }

            pkey = load_pubkey(infile, tmpformat, 1, passin, e, "Public Key");
        } else {
            pkey = load_key(infile, informat, 1, passin, e, "Private Key");
        }

        if (pkey != NULL)
            rsa = EVP_PKEY_get1_RSA(pkey);
        EVP_PKEY_free(pkey);
    }

    if (rsa == NULL) {
        ERR_print_errors(bio_err);
        goto end;
    }

    out = bio_open_owner(outfile, outformat, private);
    if (out == NULL)
        goto end;

    if (text) {
        assert(pubin || private);
        if (!RSA_print(out, rsa, 0)) {
            perror(outfile);
            ERR_print_errors(bio_err);
            goto end;
        }
    }

    if (modulus) {
        const BIGNUM *n;
        RSA_get0_key(rsa, &n, NULL, NULL);
        BIO_printf(out, "Modulus=");
        BN_print(out, n);
        BIO_printf(out, "\n");
    }

    if (check) {
        int r = RSA_check_key_ex(rsa, NULL);

        if (r == 1) {
            BIO_printf(out, "RSA key ok\n");
        } else if (r == 0) {
            unsigned long err;

            while ((err = ERR_peek_error()) != 0 &&
                   ERR_GET_LIB(err) == ERR_LIB_RSA &&
                   ERR_GET_REASON(err) != ERR_R_MALLOC_FAILURE) {
                BIO_printf(out, "RSA key error: %s\n",
                           ERR_reason_error_string(err));
                ERR_get_error(); /* remove err from error stack */
            }
        } else if (r == -1) {
            ERR_print_errors(bio_err);
            goto end;
        }
    }

    if (noout) {
        ret = 0;
        goto end;
    }
    BIO_printf(bio_err, "writing RSA key\n");
    if (outformat == FORMAT_ASN1) {
        if (pubout || pubin) {
            if (pubout == 2)
                i = i2d_RSAPublicKey_bio(out, rsa);
            else
                i = i2d_RSA_PUBKEY_bio(out, rsa);
        } else {
            assert(private);
            i = i2d_RSAPrivateKey_bio(out, rsa);
        }
    } else if (outformat == FORMAT_PEM) {
        if (pubout || pubin) {
            if (pubout == 2)
                i = PEM_write_bio_RSAPublicKey(out, rsa);
            else
                i = PEM_write_bio_RSA_PUBKEY(out, rsa);
        } else {
            assert(private);
            i = PEM_write_bio_RSAPrivateKey(out, rsa,
                                            enc, NULL, 0, NULL, passout);
        }
# ifndef OPENSSL_NO_DSA
    } else if (outformat == FORMAT_MSBLOB || outformat == FORMAT_PVK) {
        EVP_PKEY *pk;
        pk = EVP_PKEY_new();
        if (pk == NULL)
            goto end;

        EVP_PKEY_set1_RSA(pk, rsa);
        if (outformat == FORMAT_PVK) {
            if (pubin) {
                BIO_printf(bio_err, "PVK form impossible with public key input\n");
                EVP_PKEY_free(pk);
                goto end;
            }
            assert(private);
#  ifdef OPENSSL_NO_RC4
            BIO_printf(bio_err, "PVK format not supported\n");
            EVP_PKEY_free(pk);
            goto end;
#  else
            i = i2b_PVK_bio(out, pk, pvk_encr, 0, passout);
#  endif
        } else if (pubin || pubout) {
            i = i2b_PublicKey_bio(out, pk);
        } else {
            assert(private);
            i = i2b_PrivateKey_bio(out, pk);
        }
        EVP_PKEY_free(pk);
# endif
    } else {
        BIO_printf(bio_err, "bad output format specified for outfile\n");
        goto end;
    }
    if (i <= 0) {
        BIO_printf(bio_err, "unable to write key\n");
        ERR_print_errors(bio_err);
    } else {
        ret = 0;
    }
 end:
    release_engine(e);
    BIO_free_all(out);
    RSA_free(rsa);
    OPENSSL_free(passin);
    OPENSSL_free(passout);
    return ret;
}