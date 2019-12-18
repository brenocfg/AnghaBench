#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* spkac; } ;
struct TYPE_12__ {int /*<<< orphan*/  challenge; } ;
typedef  int OPTION_CHOICE ;
typedef  TYPE_2__ NETSCAPE_SPKI ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  CONF ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_set (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int FORMAT_PEM ; 
 int /*<<< orphan*/  FORMAT_TEXT ; 
 int /*<<< orphan*/  NCONF_free (int /*<<< orphan*/ *) ; 
 char* NCONF_get_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 TYPE_2__* NETSCAPE_SPKI_b64_decode (char*,int) ; 
 char* NETSCAPE_SPKI_b64_encode (TYPE_2__*) ; 
 int /*<<< orphan*/  NETSCAPE_SPKI_free (TYPE_2__*) ; 
 int /*<<< orphan*/ * NETSCAPE_SPKI_get_pubkey (TYPE_2__*) ; 
 TYPE_2__* NETSCAPE_SPKI_new () ; 
 int /*<<< orphan*/  NETSCAPE_SPKI_print (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  NETSCAPE_SPKI_set_pubkey (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NETSCAPE_SPKI_sign (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NETSCAPE_SPKI_verify (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
#define  OPT_CHALLENGE 142 
#define  OPT_ENGINE 141 
#define  OPT_EOF 140 
#define  OPT_ERR 139 
 int /*<<< orphan*/  OPT_FMT_ANY ; 
#define  OPT_HELP 138 
#define  OPT_IN 137 
#define  OPT_KEY 136 
#define  OPT_KEYFORM 135 
#define  OPT_NOOUT 134 
#define  OPT_OUT 133 
#define  OPT_PASSIN 132 
#define  OPT_PUBKEY 131 
#define  OPT_SPKAC 130 
#define  OPT_SPKSECT 129 
#define  OPT_VERIFY 128 
 int /*<<< orphan*/  PEM_write_bio_PUBKEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * app_load_config (char*) ; 
 int /*<<< orphan*/  app_passwd (char*,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * load_key (char*,int,int,char*,int /*<<< orphan*/ *,char*) ; 
 void* opt_arg () ; 
 int /*<<< orphan*/  opt_format (void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 int /*<<< orphan*/  release_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setup_engine (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spkac_options ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

int spkac_main(int argc, char **argv)
{
    BIO *out = NULL;
    CONF *conf = NULL;
    ENGINE *e = NULL;
    EVP_PKEY *pkey = NULL;
    NETSCAPE_SPKI *spki = NULL;
    char *challenge = NULL, *keyfile = NULL;
    char *infile = NULL, *outfile = NULL, *passinarg = NULL, *passin = NULL;
    char *spkstr = NULL, *prog;
    const char *spkac = "SPKAC", *spksect = "default";
    int i, ret = 1, verify = 0, noout = 0, pubkey = 0;
    int keyformat = FORMAT_PEM;
    OPTION_CHOICE o;

    prog = opt_init(argc, argv, spkac_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(spkac_options);
            ret = 0;
            goto end;
        case OPT_IN:
            infile = opt_arg();
            break;
        case OPT_OUT:
            outfile = opt_arg();
            break;
        case OPT_NOOUT:
            noout = 1;
            break;
        case OPT_PUBKEY:
            pubkey = 1;
            break;
        case OPT_VERIFY:
            verify = 1;
            break;
        case OPT_PASSIN:
            passinarg = opt_arg();
            break;
        case OPT_KEY:
            keyfile = opt_arg();
            break;
        case OPT_KEYFORM:
            if (!opt_format(opt_arg(), OPT_FMT_ANY, &keyformat))
                goto opthelp;
            break;
        case OPT_CHALLENGE:
            challenge = opt_arg();
            break;
        case OPT_SPKAC:
            spkac = opt_arg();
            break;
        case OPT_SPKSECT:
            spksect = opt_arg();
            break;
        case OPT_ENGINE:
            e = setup_engine(opt_arg(), 0);
            break;
        }
    }
    argc = opt_num_rest();
    if (argc != 0)
        goto opthelp;

    if (!app_passwd(passinarg, NULL, &passin, NULL)) {
        BIO_printf(bio_err, "Error getting password\n");
        goto end;
    }

    if (keyfile != NULL) {
        pkey = load_key(strcmp(keyfile, "-") ? keyfile : NULL,
                        keyformat, 1, passin, e, "private key");
        if (pkey == NULL)
            goto end;
        spki = NETSCAPE_SPKI_new();
        if (spki == NULL)
            goto end;
        if (challenge != NULL)
            ASN1_STRING_set(spki->spkac->challenge,
                            challenge, (int)strlen(challenge));
        NETSCAPE_SPKI_set_pubkey(spki, pkey);
        NETSCAPE_SPKI_sign(spki, pkey, EVP_md5());
        spkstr = NETSCAPE_SPKI_b64_encode(spki);
        if (spkstr == NULL)
            goto end;

        out = bio_open_default(outfile, 'w', FORMAT_TEXT);
        if (out == NULL) {
            OPENSSL_free(spkstr);
            goto end;
        }
        BIO_printf(out, "SPKAC=%s\n", spkstr);
        OPENSSL_free(spkstr);
        ret = 0;
        goto end;
    }

    if ((conf = app_load_config(infile)) == NULL)
        goto end;

    spkstr = NCONF_get_string(conf, spksect, spkac);

    if (spkstr == NULL) {
        BIO_printf(bio_err, "Can't find SPKAC called \"%s\"\n", spkac);
        ERR_print_errors(bio_err);
        goto end;
    }

    spki = NETSCAPE_SPKI_b64_decode(spkstr, -1);

    if (spki == NULL) {
        BIO_printf(bio_err, "Error loading SPKAC\n");
        ERR_print_errors(bio_err);
        goto end;
    }

    out = bio_open_default(outfile, 'w', FORMAT_TEXT);
    if (out == NULL)
        goto end;

    if (!noout)
        NETSCAPE_SPKI_print(out, spki);
    pkey = NETSCAPE_SPKI_get_pubkey(spki);
    if (verify) {
        i = NETSCAPE_SPKI_verify(spki, pkey);
        if (i > 0) {
            BIO_printf(bio_err, "Signature OK\n");
        } else {
            BIO_printf(bio_err, "Signature Failure\n");
            ERR_print_errors(bio_err);
            goto end;
        }
    }
    if (pubkey)
        PEM_write_bio_PUBKEY(out, pkey);

    ret = 0;

 end:
    NCONF_free(conf);
    NETSCAPE_SPKI_free(spki);
    BIO_free_all(out);
    EVP_PKEY_free(pkey);
    release_engine(e);
    OPENSSL_free(passin);
    return ret;
}