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

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int OPENSSL_INFO_CONFIG_DIR ; 
 int OPENSSL_INFO_DIR_FILENAME_SEPARATOR ; 
 int OPENSSL_INFO_DSO_EXTENSION ; 
 int OPENSSL_INFO_ENGINES_DIR ; 
 int OPENSSL_INFO_LIST_SEPARATOR ; 
 int OPENSSL_INFO_MODULES_DIR ; 
 char* OPENSSL_info (int) ; 
#define  OPT_CONFIGDIR 136 
#define  OPT_DIRNAMESEP 135 
#define  OPT_DSOEXT 134 
#define  OPT_ENGINESDIR 133 
#define  OPT_EOF 132 
#define  OPT_ERR 131 
#define  OPT_HELP 130 
#define  OPT_LISTSEP 129 
#define  OPT_MODULESDIR 128 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  bio_out ; 
 int /*<<< orphan*/  info_options ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 scalar_t__ opt_num_rest () ; 

int info_main(int argc, char **argv)
{
    int ret = 1, dirty = 0, type = 0;
    char *prog;
    OPTION_CHOICE o;

    prog = opt_init(argc, argv, info_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(info_options);
            ret = 0;
            goto end;
        case OPT_CONFIGDIR:
            type = OPENSSL_INFO_CONFIG_DIR;
            dirty++;
            break;
        case OPT_ENGINESDIR:
            type = OPENSSL_INFO_ENGINES_DIR;
            dirty++;
            break;
        case OPT_MODULESDIR:
            type = OPENSSL_INFO_MODULES_DIR;
            dirty++;
            break;
        case OPT_DSOEXT:
            type = OPENSSL_INFO_DSO_EXTENSION;
            dirty++;
            break;
        case OPT_DIRNAMESEP:
            type = OPENSSL_INFO_DIR_FILENAME_SEPARATOR;
            dirty++;
            break;
        case OPT_LISTSEP:
            type = OPENSSL_INFO_LIST_SEPARATOR;
            dirty++;
            break;
        }
    }
    if (opt_num_rest() != 0) {
        BIO_printf(bio_err, "%s: Extra parameters given.\n", prog);
        goto opthelp;
    }
    if (dirty > 1) {
        BIO_printf(bio_err, "%s: Only one item allowed\n", prog);
        goto opthelp;
    }
    if (dirty == 0) {
        BIO_printf(bio_err, "%s: No items chosen\n", prog);
        goto opthelp;
    }

    BIO_printf(bio_out, "%s\n", OPENSSL_info(type));
    ret = 0;
 end:
    return ret;
}