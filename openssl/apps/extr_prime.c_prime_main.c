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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* BN_bn2dec (int /*<<< orphan*/ *) ; 
 char* BN_bn2hex (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_check_prime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BN_dec2bn (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_generate_prime_ex (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BN_hex2bn (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
#define  OPT_BITS 135 
#define  OPT_CHECKS 134 
#define  OPT_EOF 133 
#define  OPT_ERR 132 
#define  OPT_GENERATE 131 
#define  OPT_HELP 130 
#define  OPT_HEX 129 
#define  OPT_SAFE 128 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  bio_out ; 
 int /*<<< orphan*/  opt_arg () ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 char** opt_rest () ; 
 int /*<<< orphan*/  prime_options ; 

int prime_main(int argc, char **argv)
{
    BIGNUM *bn = NULL;
    int hex = 0, generate = 0, bits = 0, safe = 0, ret = 1;
    char *prog;
    OPTION_CHOICE o;

    prog = opt_init(argc, argv, prime_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(prime_options);
            ret = 0;
            goto end;
        case OPT_HEX:
            hex = 1;
            break;
        case OPT_GENERATE:
            generate = 1;
            break;
        case OPT_BITS:
            bits = atoi(opt_arg());
            break;
        case OPT_SAFE:
            safe = 1;
            break;
        case OPT_CHECKS:
            /* ignore parameter and argument */
            opt_arg();
            break;
        }
    }
    argc = opt_num_rest();
    argv = opt_rest();

    if (generate) {
        if (argc != 0) {
            BIO_printf(bio_err, "Extra arguments given.\n");
            goto opthelp;
        }
    } else if (argc == 0) {
        BIO_printf(bio_err, "%s: No prime specified\n", prog);
        goto opthelp;
    }

    if (generate) {
        char *s;

        if (!bits) {
            BIO_printf(bio_err, "Specify the number of bits.\n");
            goto end;
        }
        bn = BN_new();
        if (bn == NULL) {
            BIO_printf(bio_err, "Out of memory.\n");
            goto end;
        }
        if (!BN_generate_prime_ex(bn, bits, safe, NULL, NULL, NULL)) {
            BIO_printf(bio_err, "Failed to generate prime.\n");
            goto end;
        }
        s = hex ? BN_bn2hex(bn) : BN_bn2dec(bn);
        if (s == NULL) {
            BIO_printf(bio_err, "Out of memory.\n");
            goto end;
        }
        BIO_printf(bio_out, "%s\n", s);
        OPENSSL_free(s);
    } else {
        for ( ; *argv; argv++) {
            int r;

            if (hex)
                r = BN_hex2bn(&bn, argv[0]);
            else
                r = BN_dec2bn(&bn, argv[0]);

            if (!r) {
                BIO_printf(bio_err, "Failed to process value (%s)\n", argv[0]);
                goto end;
            }

            BN_print(bio_out, bn);
            BIO_printf(bio_out, " (%s) %s prime\n",
                       argv[0],
                       BN_check_prime(bn, NULL, NULL)
                           ? "is" : "is not");
        }
    }

    ret = 0;
 end:
    BN_free(bn);
    return ret;
}