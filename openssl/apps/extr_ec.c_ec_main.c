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
typedef  int point_conversion_form_t ;
typedef  int OPTION_CHOICE ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int EC_KEY_check_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_KEY_set_asn1_flag (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EC_KEY_set_conv_form (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EC_KEY_set_enc_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_PKEY_NO_PUBKEY ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_EC_KEY (int /*<<< orphan*/ *) ; 
 int FORMAT_ASN1 ; 
 int FORMAT_ENGINE ; 
 int FORMAT_PEM ; 
 int OPENSSL_EC_NAMED_CURVE ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
#define  OPT_CHECK 147 
#define  OPT_CIPHER 146 
#define  OPT_CONV_FORM 145 
#define  OPT_ENGINE 144 
#define  OPT_EOF 143 
#define  OPT_ERR 142 
 int /*<<< orphan*/  OPT_FMT_ANY ; 
 int /*<<< orphan*/  OPT_FMT_PEMDER ; 
#define  OPT_HELP 141 
#define  OPT_IN 140 
#define  OPT_INFORM 139 
#define  OPT_NOOUT 138 
#define  OPT_NO_PUBLIC 137 
#define  OPT_OUT 136 
#define  OPT_OUTFORM 135 
#define  OPT_PARAM_ENC 134 
#define  OPT_PARAM_OUT 133 
#define  OPT_PASSIN 132 
#define  OPT_PASSOUT 131 
#define  OPT_PUBIN 130 
#define  OPT_PUBOUT 129 
#define  OPT_TEXT 128 
 int /*<<< orphan*/ * PEM_read_bio_ECPrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PEM_read_bio_EC_PUBKEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PEM_write_bio_ECPKParameters (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int PEM_write_bio_ECPrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int PEM_write_bio_EC_PUBKEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int POINT_CONVERSION_UNCOMPRESSED ; 
 int /*<<< orphan*/  app_passwd (char*,char*,char**,char**) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char*,char,int) ; 
 int /*<<< orphan*/ * bio_open_owner (char*,int,int) ; 
 int /*<<< orphan*/  conv_forms ; 
 int /*<<< orphan*/ * d2i_ECPrivateKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_EC_PUBKEY_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ec_options ; 
 int i2d_ECPKParameters_bio (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int i2d_ECPrivateKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i2d_EC_PUBKEY_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * load_key (char*,int,int,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * load_pubkey (char*,int,int,char*,int /*<<< orphan*/ *,char*) ; 
 char* opt_arg () ; 
 int /*<<< orphan*/  opt_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  opt_format (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 int /*<<< orphan*/  opt_pair (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  opt_unknown () ; 
 int /*<<< orphan*/  param_enc ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  release_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setup_engine (char*,int /*<<< orphan*/ ) ; 

int ec_main(int argc, char **argv)
{
    BIO *in = NULL, *out = NULL;
    ENGINE *e = NULL;
    EC_KEY *eckey = NULL;
    const EC_GROUP *group;
    const EVP_CIPHER *enc = NULL;
    point_conversion_form_t form = POINT_CONVERSION_UNCOMPRESSED;
    char *infile = NULL, *outfile = NULL, *prog;
    char *passin = NULL, *passout = NULL, *passinarg = NULL, *passoutarg = NULL;
    OPTION_CHOICE o;
    int asn1_flag = OPENSSL_EC_NAMED_CURVE, new_form = 0, new_asn1_flag = 0;
    int informat = FORMAT_PEM, outformat = FORMAT_PEM, text = 0, noout = 0;
    int pubin = 0, pubout = 0, param_out = 0, i, ret = 1, private = 0;
    int no_public = 0, check = 0;

    prog = opt_init(argc, argv, ec_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(ec_options);
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
            if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &outformat))
                goto opthelp;
            break;
        case OPT_OUT:
            outfile = opt_arg();
            break;
        case OPT_NOOUT:
            noout = 1;
            break;
        case OPT_TEXT:
            text = 1;
            break;
        case OPT_PARAM_OUT:
            param_out = 1;
            break;
        case OPT_PUBIN:
            pubin = 1;
            break;
        case OPT_PUBOUT:
            pubout = 1;
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
        case OPT_CIPHER:
            if (!opt_cipher(opt_unknown(), &enc))
                goto opthelp;
            break;
        case OPT_CONV_FORM:
            if (!opt_pair(opt_arg(), conv_forms, &i))
                goto opthelp;
            new_form = 1;
            form = i;
            break;
        case OPT_PARAM_ENC:
            if (!opt_pair(opt_arg(), param_enc, &i))
                goto opthelp;
            new_asn1_flag = 1;
            asn1_flag = i;
            break;
        case OPT_NO_PUBLIC:
            no_public = 1;
            break;
        case OPT_CHECK:
            check = 1;
            break;
        }
    }
    argc = opt_num_rest();
    if (argc != 0)
        goto opthelp;

    private = param_out || pubin || pubout ? 0 : 1;
    if (text && !pubin)
        private = 1;

    if (!app_passwd(passinarg, passoutarg, &passin, &passout)) {
        BIO_printf(bio_err, "Error getting passwords\n");
        goto end;
    }

    if (informat != FORMAT_ENGINE) {
        in = bio_open_default(infile, 'r', informat);
        if (in == NULL)
            goto end;
    }

    BIO_printf(bio_err, "read EC key\n");
    if (informat == FORMAT_ASN1) {
        if (pubin)
            eckey = d2i_EC_PUBKEY_bio(in, NULL);
        else
            eckey = d2i_ECPrivateKey_bio(in, NULL);
    } else if (informat == FORMAT_ENGINE) {
        EVP_PKEY *pkey;
        if (pubin)
            pkey = load_pubkey(infile, informat, 1, passin, e, "Public Key");
        else
            pkey = load_key(infile, informat, 1, passin, e, "Private Key");
        if (pkey != NULL) {
            eckey = EVP_PKEY_get1_EC_KEY(pkey);
            EVP_PKEY_free(pkey);
        }
    } else {
        if (pubin)
            eckey = PEM_read_bio_EC_PUBKEY(in, NULL, NULL, NULL);
        else
            eckey = PEM_read_bio_ECPrivateKey(in, NULL, NULL, passin);
    }
    if (eckey == NULL) {
        BIO_printf(bio_err, "unable to load Key\n");
        ERR_print_errors(bio_err);
        goto end;
    }

    out = bio_open_owner(outfile, outformat, private);
    if (out == NULL)
        goto end;

    group = EC_KEY_get0_group(eckey);

    if (new_form)
        EC_KEY_set_conv_form(eckey, form);

    if (new_asn1_flag)
        EC_KEY_set_asn1_flag(eckey, asn1_flag);

    if (no_public)
        EC_KEY_set_enc_flags(eckey, EC_PKEY_NO_PUBKEY);

    if (text) {
        assert(pubin || private);
        if (!EC_KEY_print(out, eckey, 0)) {
            perror(outfile);
            ERR_print_errors(bio_err);
            goto end;
        }
    }

    if (check) {
        if (EC_KEY_check_key(eckey) == 1) {
            BIO_printf(bio_err, "EC Key valid.\n");
        } else {
            BIO_printf(bio_err, "EC Key Invalid!\n");
            ERR_print_errors(bio_err);
        }
    }

    if (noout) {
        ret = 0;
        goto end;
    }

    BIO_printf(bio_err, "writing EC key\n");
    if (outformat == FORMAT_ASN1) {
        if (param_out) {
            i = i2d_ECPKParameters_bio(out, group);
        } else if (pubin || pubout) {
            i = i2d_EC_PUBKEY_bio(out, eckey);
        } else {
            assert(private);
            i = i2d_ECPrivateKey_bio(out, eckey);
        }
    } else {
        if (param_out) {
            i = PEM_write_bio_ECPKParameters(out, group);
        } else if (pubin || pubout) {
            i = PEM_write_bio_EC_PUBKEY(out, eckey);
        } else {
            assert(private);
            i = PEM_write_bio_ECPrivateKey(out, eckey, enc,
                                           NULL, 0, NULL, passout);
        }
    }

    if (!i) {
        BIO_printf(bio_err, "unable to write private key\n");
        ERR_print_errors(bio_err);
    } else {
        ret = 0;
    }
 end:
    BIO_free(in);
    BIO_free_all(out);
    EC_KEY_free(eckey);
    release_engine(e);
    OPENSSL_free(passin);
    OPENSSL_free(passout);
    return ret;
}