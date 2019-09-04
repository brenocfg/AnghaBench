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
typedef  int OPTION_CHOICE ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  DSA ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BN_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_DSA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_PKEY_set1_DSA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int FORMAT_ASN1 ; 
 int FORMAT_MSBLOB ; 
 int FORMAT_PEM ; 
 int FORMAT_PVK ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
#define  OPT_CIPHER 146 
#define  OPT_ENGINE 145 
#define  OPT_EOF 144 
#define  OPT_ERR 143 
 int /*<<< orphan*/  OPT_FMT_ANY ; 
#define  OPT_HELP 142 
#define  OPT_IN 141 
#define  OPT_INFORM 140 
#define  OPT_MODULUS 139 
#define  OPT_NOOUT 138 
#define  OPT_OUT 137 
#define  OPT_OUTFORM 136 
#define  OPT_PASSIN 135 
#define  OPT_PASSOUT 134 
#define  OPT_PUBIN 133 
#define  OPT_PUBOUT 132 
#define  OPT_PVK_NONE 131 
#define  OPT_PVK_STRONG 130 
#define  OPT_PVK_WEAK 129 
#define  OPT_TEXT 128 
 int PEM_write_bio_DSAPrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int PEM_write_bio_DSA_PUBKEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  app_passwd (char*,char*,char**,char**) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * bio_err ; 
 int /*<<< orphan*/ * bio_open_owner (char*,int,int) ; 
 int /*<<< orphan*/  dsa_options ; 
 int i2b_PVK_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int i2b_PrivateKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i2b_PublicKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i2d_DSAPrivateKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i2d_DSA_PUBKEY_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
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
 int /*<<< orphan*/ * setup_engine (char*,int /*<<< orphan*/ ) ; 

int dsa_main(int argc, char **argv)
{
    BIO *out = NULL;
    DSA *dsa = NULL;
    ENGINE *e = NULL;
    const EVP_CIPHER *enc = NULL;
    char *infile = NULL, *outfile = NULL, *prog;
    char *passin = NULL, *passout = NULL, *passinarg = NULL, *passoutarg = NULL;
    OPTION_CHOICE o;
    int informat = FORMAT_PEM, outformat = FORMAT_PEM, text = 0, noout = 0;
    int i, modulus = 0, pubin = 0, pubout = 0, ret = 1;
# ifndef OPENSSL_NO_RC4
    int pvk_encr = 2;
# endif
    int private = 0;

    prog = opt_init(argc, argv, dsa_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            ret = 0;
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(dsa_options);
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
        case OPT_ENGINE:
            e = setup_engine(opt_arg(), 0);
            break;
        case OPT_PASSIN:
            passinarg = opt_arg();
            break;
        case OPT_PASSOUT:
            passoutarg = opt_arg();
            break;
        case OPT_PVK_STRONG:    /* pvk_encr:= 2 */
        case OPT_PVK_WEAK:      /* pvk_encr:= 1 */
        case OPT_PVK_NONE:      /* pvk_encr:= 0 */
#ifndef OPENSSL_NO_RC4
            pvk_encr = (o - OPT_PVK_NONE);
#endif
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
        case OPT_PUBIN:
            pubin = 1;
            break;
        case OPT_PUBOUT:
            pubout = 1;
            break;
        case OPT_CIPHER:
            if (!opt_cipher(opt_unknown(), &enc))
                goto end;
            break;
        }
    }
    argc = opt_num_rest();
    if (argc != 0)
        goto opthelp;

    private = pubin || pubout ? 0 : 1;
    if (text && !pubin)
        private = 1;

    if (!app_passwd(passinarg, passoutarg, &passin, &passout)) {
        BIO_printf(bio_err, "Error getting passwords\n");
        goto end;
    }

    BIO_printf(bio_err, "read DSA key\n");
    {
        EVP_PKEY *pkey;

        if (pubin)
            pkey = load_pubkey(infile, informat, 1, passin, e, "Public Key");
        else
            pkey = load_key(infile, informat, 1, passin, e, "Private Key");

        if (pkey != NULL) {
            dsa = EVP_PKEY_get1_DSA(pkey);
            EVP_PKEY_free(pkey);
        }
    }
    if (dsa == NULL) {
        BIO_printf(bio_err, "unable to load Key\n");
        ERR_print_errors(bio_err);
        goto end;
    }

    out = bio_open_owner(outfile, outformat, private);
    if (out == NULL)
        goto end;

    if (text) {
        assert(pubin || private);
        if (!DSA_print(out, dsa, 0)) {
            perror(outfile);
            ERR_print_errors(bio_err);
            goto end;
        }
    }

    if (modulus) {
        const BIGNUM *pub_key = NULL;
        DSA_get0_key(dsa, &pub_key, NULL);
        BIO_printf(out, "Public Key=");
        BN_print(out, pub_key);
        BIO_printf(out, "\n");
    }

    if (noout) {
        ret = 0;
        goto end;
    }
    BIO_printf(bio_err, "writing DSA key\n");
    if (outformat == FORMAT_ASN1) {
        if (pubin || pubout) {
            i = i2d_DSA_PUBKEY_bio(out, dsa);
        } else {
            assert(private);
            i = i2d_DSAPrivateKey_bio(out, dsa);
        }
    } else if (outformat == FORMAT_PEM) {
        if (pubin || pubout) {
            i = PEM_write_bio_DSA_PUBKEY(out, dsa);
        } else {
            assert(private);
            i = PEM_write_bio_DSAPrivateKey(out, dsa, enc,
                                            NULL, 0, NULL, passout);
        }
# ifndef OPENSSL_NO_RSA
    } else if (outformat == FORMAT_MSBLOB || outformat == FORMAT_PVK) {
        EVP_PKEY *pk;
        pk = EVP_PKEY_new();
        if (pk == NULL)
           goto end;

        EVP_PKEY_set1_DSA(pk, dsa);
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
        BIO_printf(bio_err, "unable to write private key\n");
        ERR_print_errors(bio_err);
        goto end;
    }
    ret = 0;
 end:
    BIO_free_all(out);
    DSA_free(dsa);
    release_engine(e);
    OPENSSL_free(passin);
    OPENSSL_free(passout);
    return ret;
}