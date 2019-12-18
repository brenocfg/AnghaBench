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
typedef  int /*<<< orphan*/  X509_VERIFY_PARAM ;
typedef  int OPTION_CHOICE ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  EXACTLY_ONE (char*,char*,char*) ; 
 int /*<<< orphan*/  NCONF_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
#define  OPT_CAFILE 158 
#define  OPT_CAPATH 157 
#define  OPT_CASTORE 156 
#define  OPT_CERT 155 
#define  OPT_CHAIN 154 
#define  OPT_CONFIG 153 
#define  OPT_DATA 152 
#define  OPT_DIGEST 151 
#define  OPT_ENGINE 150 
#define  OPT_EOF 149 
#define  OPT_ERR 148 
#define  OPT_HELP 147 
#define  OPT_IN 146 
#define  OPT_INKEY 145 
#define  OPT_MD 144 
#define  OPT_NO_NONCE 143 
#define  OPT_OUT 142 
#define  OPT_PASSIN 141 
#define  OPT_QUERY 140 
#define  OPT_QUERYFILE 139 
#define  OPT_REPLY 138 
#define  OPT_R_CASES 137 
#define  OPT_SECTION 136 
#define  OPT_SIGNER 135 
#define  OPT_TEXT 134 
#define  OPT_TOKEN_IN 133 
#define  OPT_TOKEN_OUT 132 
#define  OPT_TSPOLICY 131 
#define  OPT_UNTRUSTED 130 
#define  OPT_VERIFY 129 
#define  OPT_V_CASES 128 
 int /*<<< orphan*/  X509_VERIFY_PARAM_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_VERIFY_PARAM_new () ; 
 int /*<<< orphan*/  app_load_modules (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  app_passwd (char*,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 char const* default_config_file ; 
 int /*<<< orphan*/ * load_config_file (char const*) ; 
 void* opt_arg () ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char** opt_helplist ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_md (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int opt_next () ; 
 scalar_t__ opt_num_rest () ; 
 int /*<<< orphan*/  opt_rand (int) ; 
 int /*<<< orphan*/  opt_unknown () ; 
 int /*<<< orphan*/  opt_verify (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  query_command (char*,char*,int /*<<< orphan*/  const*,char*,int,int,char*,char*,int) ; 
 int /*<<< orphan*/  reply_command (int /*<<< orphan*/ *,char const*,char const*,char*,char*,char*,int /*<<< orphan*/  const*,char*,char*,char*,char*,int,char*,int,int) ; 
 int /*<<< orphan*/  ts_options ; 
 int /*<<< orphan*/  verify_command (char*,char*,char*,char*,int,char*,char const*,char*,char const*,int /*<<< orphan*/ *) ; 

int ts_main(int argc, char **argv)
{
    CONF *conf = NULL;
    const char *CAfile = NULL, *untrusted = NULL, *prog;
    const char *configfile = default_config_file, *engine = NULL;
    const char *section = NULL;
    char **helpp;
    char *password = NULL;
    char *data = NULL, *digest = NULL, *policy = NULL;
    char *in = NULL, *out = NULL, *queryfile = NULL, *passin = NULL;
    char *inkey = NULL, *signer = NULL, *chain = NULL, *CApath = NULL;
    char *CAstore = NULL;
    const EVP_MD *md = NULL;
    OPTION_CHOICE o, mode = OPT_ERR;
    int ret = 1, no_nonce = 0, cert = 0, text = 0;
    int vpmtouched = 0;
    X509_VERIFY_PARAM *vpm = NULL;
    /* Input is ContentInfo instead of TimeStampResp. */
    int token_in = 0;
    /* Output is ContentInfo instead of TimeStampResp. */
    int token_out = 0;

    if ((vpm = X509_VERIFY_PARAM_new()) == NULL)
        goto end;

    prog = opt_init(argc, argv, ts_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(ts_options);
            for (helpp = opt_helplist; *helpp; ++helpp)
                BIO_printf(bio_err, "%s\n", *helpp);
            ret = 0;
            goto end;
        case OPT_CONFIG:
            configfile = opt_arg();
            break;
        case OPT_SECTION:
            section = opt_arg();
            break;
        case OPT_QUERY:
        case OPT_REPLY:
        case OPT_VERIFY:
            if (mode != OPT_ERR)
                goto opthelp;
            mode = o;
            break;
        case OPT_DATA:
            data = opt_arg();
            break;
        case OPT_DIGEST:
            digest = opt_arg();
            break;
        case OPT_R_CASES:
            if (!opt_rand(o))
                goto end;
            break;
        case OPT_TSPOLICY:
            policy = opt_arg();
            break;
        case OPT_NO_NONCE:
            no_nonce = 1;
            break;
        case OPT_CERT:
            cert = 1;
            break;
        case OPT_IN:
            in = opt_arg();
            break;
        case OPT_TOKEN_IN:
            token_in = 1;
            break;
        case OPT_OUT:
            out = opt_arg();
            break;
        case OPT_TOKEN_OUT:
            token_out = 1;
            break;
        case OPT_TEXT:
            text = 1;
            break;
        case OPT_QUERYFILE:
            queryfile = opt_arg();
            break;
        case OPT_PASSIN:
            passin = opt_arg();
            break;
        case OPT_INKEY:
            inkey = opt_arg();
            break;
        case OPT_SIGNER:
            signer = opt_arg();
            break;
        case OPT_CHAIN:
            chain = opt_arg();
            break;
        case OPT_CAPATH:
            CApath = opt_arg();
            break;
        case OPT_CAFILE:
            CAfile = opt_arg();
            break;
        case OPT_CASTORE:
            CAstore = opt_arg();
            break;
        case OPT_UNTRUSTED:
            untrusted = opt_arg();
            break;
        case OPT_ENGINE:
            engine = opt_arg();
            break;
        case OPT_MD:
            if (!opt_md(opt_unknown(), &md))
                goto opthelp;
            break;
        case OPT_V_CASES:
            if (!opt_verify(o, vpm))
                goto end;
            vpmtouched++;
            break;
        }
    }
    if (mode == OPT_ERR || opt_num_rest() != 0)
        goto opthelp;

    if (mode == OPT_REPLY && passin &&
        !app_passwd(passin, NULL, &password, NULL)) {
        BIO_printf(bio_err, "Error getting password.\n");
        goto end;
    }

    conf = load_config_file(configfile);
    if (configfile != default_config_file && !app_load_modules(conf))
        goto end;

    /* Check parameter consistency and execute the appropriate function. */
    if (mode == OPT_QUERY) {
        if (vpmtouched)
            goto opthelp;
        if ((data != NULL) && (digest != NULL))
            goto opthelp;
        ret = !query_command(data, digest, md, policy, no_nonce, cert,
                             in, out, text);
    } else if (mode == OPT_REPLY) {
        if (vpmtouched)
            goto opthelp;
        if ((in != NULL) && (queryfile != NULL))
            goto opthelp;
        if (in == NULL) {
            if ((conf == NULL) || (token_in != 0))
                goto opthelp;
        }
        ret = !reply_command(conf, section, engine, queryfile,
                             password, inkey, md, signer, chain, policy,
                             in, token_in, out, token_out, text);

    } else if (mode == OPT_VERIFY) {
        if ((in == NULL) || !EXACTLY_ONE(queryfile, data, digest))
            goto opthelp;
        ret = !verify_command(data, digest, queryfile, in, token_in,
                              CApath, CAfile, CAstore, untrusted,
                              vpmtouched ? vpm : NULL);
    } else {
        goto opthelp;
    }

 end:
    X509_VERIFY_PARAM_free(vpm);
    NCONF_free(conf);
    OPENSSL_free(password);
    return ret;
}