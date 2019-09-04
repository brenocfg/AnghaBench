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
typedef  int /*<<< orphan*/  buf ;
typedef  int OPTION_CHOICE ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ERR_error_string_n (unsigned long,char*,int) ; 
 int OPENSSL_INIT_LOAD_CRYPTO_STRINGS ; 
 int OPENSSL_INIT_LOAD_SSL_STRINGS ; 
 int /*<<< orphan*/  OPENSSL_init_ssl (int,int /*<<< orphan*/ *) ; 
#define  OPT_EOF 130 
#define  OPT_ERR 129 
#define  OPT_HELP 128 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  bio_out ; 
 int /*<<< orphan*/  errstr_options ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 char** opt_rest () ; 
 scalar_t__ sscanf (char*,char*,unsigned long*) ; 

int errstr_main(int argc, char **argv)
{
    OPTION_CHOICE o;
    char buf[256], *prog;
    int ret = 1;
    unsigned long l;

    prog = opt_init(argc, argv, errstr_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(errstr_options);
            ret = 0;
            goto end;
        }
    }

    ret = 0;
    for (argv = opt_rest(); *argv; argv++) {
        if (sscanf(*argv, "%lx", &l) == 0) {
            ret++;
        } else {
            /* We're not really an SSL application so this won't auto-init, but
             * we're still interested in SSL error strings
             */
            OPENSSL_init_ssl(OPENSSL_INIT_LOAD_SSL_STRINGS
                             | OPENSSL_INIT_LOAD_CRYPTO_STRINGS, NULL);
            ERR_error_string_n(l, buf, sizeof(buf));
            BIO_printf(bio_out, "%s\n", buf);
        }
    }
 end:
    return ret;
}