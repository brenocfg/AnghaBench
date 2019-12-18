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
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 unsigned long ERR_peek_error () ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ *) ; 
 char* ERR_reason_error_string (unsigned long) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_param_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_print_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FORMAT_PEM ; 
#define  OPT_CHECK 136 
#define  OPT_ENGINE 135 
#define  OPT_EOF 134 
#define  OPT_ERR 133 
#define  OPT_HELP 132 
#define  OPT_IN 131 
#define  OPT_NOOUT 130 
#define  OPT_OUT 129 
#define  OPT_TEXT 128 
 int /*<<< orphan*/ * PEM_read_bio_Parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_write_bio_Parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char*,char,int /*<<< orphan*/ ) ; 
 char* opt_arg () ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 int /*<<< orphan*/  pkeyparam_options ; 
 int /*<<< orphan*/  release_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setup_engine (char*,int /*<<< orphan*/ ) ; 

int pkeyparam_main(int argc, char **argv)
{
    ENGINE *e = NULL;
    BIO *in = NULL, *out = NULL;
    EVP_PKEY *pkey = NULL;
    int text = 0, noout = 0, ret = 1, check = 0;
    OPTION_CHOICE o;
    char *infile = NULL, *outfile = NULL, *prog;

    prog = opt_init(argc, argv, pkeyparam_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(pkeyparam_options);
            ret = 0;
            goto end;
        case OPT_IN:
            infile = opt_arg();
            break;
        case OPT_OUT:
            outfile = opt_arg();
            break;
        case OPT_ENGINE:
            e = setup_engine(opt_arg(), 0);
            break;
        case OPT_TEXT:
            text = 1;
            break;
        case OPT_NOOUT:
            noout = 1;
            break;
        case OPT_CHECK:
            check = 1;
            break;
        }
    }
    argc = opt_num_rest();
    if (argc != 0)
        goto opthelp;

    in = bio_open_default(infile, 'r', FORMAT_PEM);
    if (in == NULL)
        goto end;
    out = bio_open_default(outfile, 'w', FORMAT_PEM);
    if (out == NULL)
        goto end;
    pkey = PEM_read_bio_Parameters(in, NULL);
    if (pkey == NULL) {
        BIO_printf(bio_err, "Error reading parameters\n");
        ERR_print_errors(bio_err);
        goto end;
    }

    if (check) {
        int r;
        EVP_PKEY_CTX *ctx;

        ctx = EVP_PKEY_CTX_new(pkey, e);
        if (ctx == NULL) {
            ERR_print_errors(bio_err);
            goto end;
        }

        r = EVP_PKEY_param_check(ctx);

        if (r == 1) {
            BIO_printf(out, "Parameters are valid\n");
        } else {
            /*
             * Note: at least for RSA keys if this function returns
             * -1, there will be no error reasons.
             */
            unsigned long err;

            BIO_printf(out, "Parameters are invalid\n");

            while ((err = ERR_peek_error()) != 0) {
                BIO_printf(out, "Detailed error: %s\n",
                           ERR_reason_error_string(err));
                ERR_get_error(); /* remove err from error stack */
            }
        }
        EVP_PKEY_CTX_free(ctx);
    }

    if (!noout)
        PEM_write_bio_Parameters(out, pkey);

    if (text)
        EVP_PKEY_print_params(out, pkey, 0, NULL);

    ret = 0;

 end:
    EVP_PKEY_free(pkey);
    release_engine(e);
    BIO_free_all(out);
    BIO_free(in);

    return ret;
}