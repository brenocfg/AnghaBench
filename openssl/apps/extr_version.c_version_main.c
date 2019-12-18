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
 char* BF_options () ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* BN_options () ; 
 char* DES_options () ; 
 char* IDEA_options () ; 
 char* MD2_options () ; 
 int /*<<< orphan*/  OPENSSL_BUILT_ON ; 
 int /*<<< orphan*/  OPENSSL_CFLAGS ; 
 int /*<<< orphan*/  OPENSSL_CPU_INFO ; 
 int /*<<< orphan*/  OPENSSL_DIR ; 
 int /*<<< orphan*/  OPENSSL_ENGINES_DIR ; 
 int /*<<< orphan*/  OPENSSL_INFO_SEED_SOURCE ; 
 int /*<<< orphan*/  OPENSSL_MODULES_DIR ; 
 int /*<<< orphan*/  OPENSSL_PLATFORM ; 
 int /*<<< orphan*/  OPENSSL_VERSION ; 
 char* OPENSSL_VERSION_TEXT ; 
 char* OPENSSL_info (int /*<<< orphan*/ ) ; 
#define  OPT_A 141 
#define  OPT_B 140 
#define  OPT_C 139 
#define  OPT_D 138 
#define  OPT_E 137 
#define  OPT_EOF 136 
#define  OPT_ERR 135 
#define  OPT_F 134 
#define  OPT_HELP 133 
#define  OPT_M 132 
#define  OPT_O 131 
#define  OPT_P 130 
#define  OPT_R 129 
#define  OPT_V 128 
 char* OpenSSL_version (int /*<<< orphan*/ ) ; 
 char* RC4_options () ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 scalar_t__ opt_num_rest () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  version_options ; 

int version_main(int argc, char **argv)
{
    int ret = 1, dirty = 0, seed = 0;
    int cflags = 0, version = 0, date = 0, options = 0, platform = 0, dir = 0;
    int engdir = 0, moddir = 0, cpuinfo = 0;
    char *prog;
    OPTION_CHOICE o;

    prog = opt_init(argc, argv, version_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(version_options);
            ret = 0;
            goto end;
        case OPT_B:
            dirty = date = 1;
            break;
        case OPT_D:
            dirty = dir = 1;
            break;
        case OPT_E:
            dirty = engdir = 1;
            break;
        case OPT_M:
            dirty = moddir = 1;
            break;
        case OPT_F:
            dirty = cflags = 1;
            break;
        case OPT_O:
            dirty = options = 1;
            break;
        case OPT_P:
            dirty = platform = 1;
            break;
        case OPT_R:
            dirty = seed = 1;
            break;
        case OPT_V:
            dirty = version = 1;
            break;
        case OPT_C:
            dirty = cpuinfo = 1;
            break;
        case OPT_A:
            seed = options = cflags = version = date = platform
                = dir = engdir = moddir = cpuinfo
                = 1;
            break;
        }
    }
    if (opt_num_rest() != 0) {
        BIO_printf(bio_err, "Extra parameters given.\n");
        goto opthelp;
    }
    if (!dirty)
        version = 1;

    if (version)
        printf("%s (Library: %s)\n",
               OPENSSL_VERSION_TEXT, OpenSSL_version(OPENSSL_VERSION));
    if (date)
        printf("%s\n", OpenSSL_version(OPENSSL_BUILT_ON));
    if (platform)
        printf("%s\n", OpenSSL_version(OPENSSL_PLATFORM));
    if (options) {
        printf("options: ");
        printf(" %s", BN_options());
#ifndef OPENSSL_NO_MD2
        printf(" %s", MD2_options());
#endif
#ifndef OPENSSL_NO_RC4
        printf(" %s", RC4_options());
#endif
#ifndef OPENSSL_NO_DES
        printf(" %s", DES_options());
#endif
#ifndef OPENSSL_NO_IDEA
        printf(" %s", IDEA_options());
#endif
#ifndef OPENSSL_NO_BF
        printf(" %s", BF_options());
#endif
        printf("\n");
    }
    if (cflags)
        printf("%s\n", OpenSSL_version(OPENSSL_CFLAGS));
    if (dir)
        printf("%s\n", OpenSSL_version(OPENSSL_DIR));
    if (engdir)
        printf("%s\n", OpenSSL_version(OPENSSL_ENGINES_DIR));
    if (moddir)
        printf("%s\n", OpenSSL_version(OPENSSL_MODULES_DIR));
    if (seed) {
        const char *src = OPENSSL_info(OPENSSL_INFO_SEED_SOURCE);
        printf("Seeding source: %s\n", src ? src : "N/A");
    }
    if (cpuinfo)
        printf("%s\n", OpenSSL_version(OPENSSL_CPU_INFO));
    ret = 0;
 end:
    return ret;
}