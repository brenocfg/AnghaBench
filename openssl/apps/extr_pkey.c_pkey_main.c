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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 unsigned long ERR_peek_error () ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_reason_error_string (unsigned long) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EVP_PKEY_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_print_private (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_print_public (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EVP_PKEY_public_check (int /*<<< orphan*/ *) ; 
 int FORMAT_ASN1 ; 
 int FORMAT_PEM ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
#define  OPT_CHECK 146 
#define  OPT_ENGINE 145 
#define  OPT_EOF 144 
#define  OPT_ERR 143 
 int /*<<< orphan*/  OPT_FMT_ANY ; 
 int /*<<< orphan*/  OPT_FMT_PEMDER ; 
#define  OPT_HELP 142 
#define  OPT_IN 141 
#define  OPT_INFORM 140 
#define  OPT_MD 139 
#define  OPT_NOOUT 138 
#define  OPT_OUT 137 
#define  OPT_OUTFORM 136 
#define  OPT_PASSIN 135 
#define  OPT_PASSOUT 134 
#define  OPT_PUBIN 133 
#define  OPT_PUBOUT 132 
#define  OPT_PUB_CHECK 131 
#define  OPT_TEXT 130 
#define  OPT_TEXT_PUB 129 
#define  OPT_TRADITIONAL 128 
 int /*<<< orphan*/  PEM_write_bio_PUBKEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_write_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PEM_write_bio_PrivateKey_traditional (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  app_passwd (char*,char*,char**,char**) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * bio_err ; 
 int /*<<< orphan*/ * bio_open_owner (char*,int,int) ; 
 int /*<<< orphan*/  i2d_PUBKEY_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2d_PrivateKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
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
 int /*<<< orphan*/  pkey_options ; 
 int /*<<< orphan*/  release_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setup_engine (char*,int /*<<< orphan*/ ) ; 

int pkey_main(int argc, char **argv)
{
    BIO *in = NULL, *out = NULL;
    ENGINE *e = NULL;
    EVP_PKEY *pkey = NULL;
    const EVP_CIPHER *cipher = NULL;
    char *infile = NULL, *outfile = NULL, *passin = NULL, *passout = NULL;
    char *passinarg = NULL, *passoutarg = NULL, *prog;
    OPTION_CHOICE o;
    int informat = FORMAT_PEM, outformat = FORMAT_PEM;
    int pubin = 0, pubout = 0, pubtext = 0, text = 0, noout = 0, ret = 1;
    int private = 0, traditional = 0, check = 0, pub_check = 0;

    prog = opt_init(argc, argv, pkey_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(pkey_options);
            ret = 0;
            goto end;
        case OPT_INFORM:
            if (!opt_format(opt_arg(), OPT_FMT_ANY, &informat))
                goto opthelp;
            break;
        case OPT_OUTFORM:
            if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &outformat))
                goto opthelp;
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
        case OPT_IN:
            infile = opt_arg();
            break;
        case OPT_OUT:
            outfile = opt_arg();
            break;
        case OPT_PUBIN:
            pubin = pubout = pubtext = 1;
            break;
        case OPT_PUBOUT:
            pubout = 1;
            break;
        case OPT_TEXT_PUB:
            pubtext = text = 1;
            break;
        case OPT_TEXT:
            text = 1;
            break;
        case OPT_NOOUT:
            noout = 1;
            break;
        case OPT_TRADITIONAL:
            traditional = 1;
            break;
        case OPT_CHECK:
            check = 1;
            break;
        case OPT_PUB_CHECK:
            pub_check = 1;
            break;
        case OPT_MD:
            if (!opt_cipher(opt_unknown(), &cipher))
                goto opthelp;
        }
    }
    argc = opt_num_rest();
    if (argc != 0)
        goto opthelp;

    private = !noout && !pubout ? 1 : 0;
    if (text && !pubtext)
        private = 1;

    if (!app_passwd(passinarg, passoutarg, &passin, &passout)) {
        BIO_printf(bio_err, "Error getting passwords\n");
        goto end;
    }

    out = bio_open_owner(outfile, outformat, private);
    if (out == NULL)
        goto end;

    if (pubin)
        pkey = load_pubkey(infile, informat, 1, passin, e, "Public Key");
    else
        pkey = load_key(infile, informat, 1, passin, e, "key");
    if (pkey == NULL)
        goto end;

    if (check || pub_check) {
        int r;
        EVP_PKEY_CTX *ctx;

        ctx = EVP_PKEY_CTX_new(pkey, e);
        if (ctx == NULL) {
            ERR_print_errors(bio_err);
            goto end;
        }

        if (check)
            r = EVP_PKEY_check(ctx);
        else
            r = EVP_PKEY_public_check(ctx);

        if (r == 1) {
            BIO_printf(out, "Key is valid\n");
        } else {
            /*
             * Note: at least for RSA keys if this function returns
             * -1, there will be no error reasons.
             */
            unsigned long err;

            BIO_printf(out, "Key is invalid\n");

            while ((err = ERR_peek_error()) != 0) {
                BIO_printf(out, "Detailed error: %s\n",
                           ERR_reason_error_string(err));
                ERR_get_error(); /* remove err from error stack */
            }
        }
        EVP_PKEY_CTX_free(ctx);
    }

    if (!noout) {
        if (outformat == FORMAT_PEM) {
            if (pubout) {
                if (!PEM_write_bio_PUBKEY(out, pkey))
                    goto end;
            } else {
                assert(private);
                if (traditional) {
                    if (!PEM_write_bio_PrivateKey_traditional(out, pkey, cipher,
                                                              NULL, 0, NULL,
                                                              passout))
                        goto end;
                } else {
                    if (!PEM_write_bio_PrivateKey(out, pkey, cipher,
                                                  NULL, 0, NULL, passout))
                        goto end;
                }
            }
        } else if (outformat == FORMAT_ASN1) {
            if (pubout) {
                if (!i2d_PUBKEY_bio(out, pkey))
                    goto end;
            } else {
                assert(private);
                if (!i2d_PrivateKey_bio(out, pkey))
                    goto end;
            }
        } else {
            BIO_printf(bio_err, "Bad format specified for key\n");
            goto end;
        }
    }

    if (text) {
        if (pubtext) {
            if (EVP_PKEY_print_public(out, pkey, 0, NULL) <= 0)
                goto end;
        } else {
            assert(private);
            if (EVP_PKEY_print_private(out, pkey, 0, NULL) <= 0)
                goto end;
        }
    }

    ret = 0;

 end:
    if (ret != 0)
        ERR_print_errors(bio_err);
    EVP_PKEY_free(pkey);
    release_engine(e);
    BIO_free_all(out);
    BIO_free(in);
    OPENSSL_free(passin);
    OPENSSL_free(passout);

    return ret;
}