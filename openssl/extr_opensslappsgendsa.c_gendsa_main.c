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
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  DSA ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_generate_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_get0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORMAT_PEM ; 
 scalar_t__ OPENSSL_DSA_MAX_MODULUS_BITS ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
#define  OPT_CIPHER 136 
#define  OPT_ENGINE 135 
#define  OPT_EOF 134 
#define  OPT_ERR 133 
#define  OPT_HELP 132 
#define  OPT_OUT 131 
#define  OPT_PASSOUT 130 
#define  OPT_R_CASES 129 
#define  OPT_VERBOSE 128 
 int /*<<< orphan*/ * PEM_read_bio_DSAparams (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_write_bio_DSAPrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  app_passwd (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bio_open_owner (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gendsa_options ; 
 char* opt_arg () ; 
 int /*<<< orphan*/  opt_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 int /*<<< orphan*/  opt_rand (int) ; 
 char** opt_rest () ; 
 int /*<<< orphan*/  opt_unknown () ; 
 int /*<<< orphan*/  release_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setup_engine (char*,int /*<<< orphan*/ ) ; 

int gendsa_main(int argc, char **argv)
{
    ENGINE *e = NULL;
    BIO *out = NULL, *in = NULL;
    DSA *dsa = NULL;
    const EVP_CIPHER *enc = NULL;
    char *dsaparams = NULL;
    char *outfile = NULL, *passoutarg = NULL, *passout = NULL, *prog;
    OPTION_CHOICE o;
    int ret = 1, private = 0, verbose = 0;
    const BIGNUM *p = NULL;

    prog = opt_init(argc, argv, gendsa_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            ret = 0;
            opt_help(gendsa_options);
            goto end;
        case OPT_OUT:
            outfile = opt_arg();
            break;
        case OPT_PASSOUT:
            passoutarg = opt_arg();
            break;
        case OPT_ENGINE:
            e = setup_engine(opt_arg(), 0);
            break;
        case OPT_R_CASES:
            if (!opt_rand(o))
                goto end;
            break;
        case OPT_CIPHER:
            if (!opt_cipher(opt_unknown(), &enc))
                goto end;
            break;
        case OPT_VERBOSE:
            verbose = 1;
            break;
        }
    }
    argc = opt_num_rest();
    argv = opt_rest();
    private = 1;

    if (argc != 1)
        goto opthelp;
    dsaparams = *argv;

    if (!app_passwd(NULL, passoutarg, NULL, &passout)) {
        BIO_printf(bio_err, "Error getting password\n");
        goto end;
    }

    in = bio_open_default(dsaparams, 'r', FORMAT_PEM);
    if (in == NULL)
        goto end2;

    if ((dsa = PEM_read_bio_DSAparams(in, NULL, NULL, NULL)) == NULL) {
        BIO_printf(bio_err, "unable to load DSA parameter file\n");
        goto end;
    }
    BIO_free(in);
    in = NULL;

    out = bio_open_owner(outfile, FORMAT_PEM, private);
    if (out == NULL)
        goto end2;

    DSA_get0_pqg(dsa, &p, NULL, NULL);

    if (BN_num_bits(p) > OPENSSL_DSA_MAX_MODULUS_BITS)
        BIO_printf(bio_err,
                   "Warning: It is not recommended to use more than %d bit for DSA keys.\n"
                   "         Your key size is %d! Larger key size may behave not as expected.\n",
                   OPENSSL_DSA_MAX_MODULUS_BITS, BN_num_bits(p));

    if (verbose)
        BIO_printf(bio_err, "Generating DSA key, %d bits\n", BN_num_bits(p));
    if (!DSA_generate_key(dsa))
        goto end;

    assert(private);
    if (!PEM_write_bio_DSAPrivateKey(out, dsa, enc, NULL, 0, NULL, passout))
        goto end;
    ret = 0;
 end:
    if (ret != 0)
        ERR_print_errors(bio_err);
 end2:
    BIO_free(in);
    BIO_free_all(out);
    DSA_free(dsa);
    release_engine(e);
    OPENSSL_free(passout);
    return ret;
}