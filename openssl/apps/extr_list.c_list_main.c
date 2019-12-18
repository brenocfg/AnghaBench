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
typedef  int HELPLIST_CHOICE ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  FT_cipher ; 
 int /*<<< orphan*/  FT_general ; 
 int /*<<< orphan*/  FT_md ; 
#define  OPT_CIPHER_ALGORITHMS 146 
#define  OPT_CIPHER_COMMANDS 145 
#define  OPT_COMMANDS 144 
#define  OPT_DIGEST_ALGORITHMS 143 
#define  OPT_DIGEST_COMMANDS 142 
#define  OPT_DISABLED 141 
#define  OPT_ENGINES 140 
#define  OPT_EOF 139 
#define  OPT_ERR 138 
#define  OPT_HELP 137 
#define  OPT_KDF_ALGORITHMS 136 
#define  OPT_MAC_ALGORITHMS 135 
#define  OPT_MISSING_HELP 134 
#define  OPT_OBJECTS 133 
#define  OPT_ONE 132 
#define  OPT_OPTIONS 131 
#define  OPT_PK_ALGORITHMS 130 
#define  OPT_PK_METHOD 129 
#define  OPT_VERBOSE 128 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  list_ciphers () ; 
 int /*<<< orphan*/  list_digests () ; 
 int /*<<< orphan*/  list_disabled () ; 
 int /*<<< orphan*/  list_engines () ; 
 int /*<<< orphan*/  list_kdfs () ; 
 int /*<<< orphan*/  list_macs () ; 
 int /*<<< orphan*/  list_missing_help () ; 
 int /*<<< orphan*/  list_objects () ; 
 int /*<<< orphan*/  list_options ; 
 int /*<<< orphan*/  list_options_for_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_pkey () ; 
 int /*<<< orphan*/  list_pkey_meth () ; 
 int /*<<< orphan*/  list_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opt_arg () ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 scalar_t__ opt_num_rest () ; 
 int verbose ; 

int list_main(int argc, char **argv)
{
    char *prog;
    HELPLIST_CHOICE o;
    int one = 0, done = 0;
    struct {
        unsigned int commands:1;
        unsigned int digest_commands:1;
        unsigned int digest_algorithms:1;
        unsigned int kdf_algorithms:1;
        unsigned int mac_algorithms:1;
        unsigned int cipher_commands:1;
        unsigned int cipher_algorithms:1;
        unsigned int pk_algorithms:1;
        unsigned int pk_method:1;
        unsigned int engines:1;
        unsigned int disabled:1;
        unsigned int missing_help:1;
        unsigned int objects:1;
        unsigned int options:1;
    } todo = { 0, };

    verbose = 0;                 /* Clear a possible previous call */

    prog = opt_init(argc, argv, list_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:  /* Never hit, but suppresses warning */
        case OPT_ERR:
opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            return 1;
        case OPT_HELP:
            opt_help(list_options);
            break;
        case OPT_ONE:
            one = 1;
            break;
        case OPT_COMMANDS:
            todo.commands = 1;
            break;
        case OPT_DIGEST_COMMANDS:
            todo.digest_commands = 1;
            break;
        case OPT_DIGEST_ALGORITHMS:
            todo.digest_algorithms = 1;
            break;
        case OPT_KDF_ALGORITHMS:
            todo.kdf_algorithms = 1;
            break;
        case OPT_MAC_ALGORITHMS:
            todo.mac_algorithms = 1;
            break;
        case OPT_CIPHER_COMMANDS:
            todo.cipher_commands = 1;
            break;
        case OPT_CIPHER_ALGORITHMS:
            todo.cipher_algorithms = 1;
            break;
        case OPT_PK_ALGORITHMS:
            todo.pk_algorithms = 1;
            break;
        case OPT_PK_METHOD:
            todo.pk_method = 1;
            break;
        case OPT_ENGINES:
            todo.engines = 1;
            break;
        case OPT_DISABLED:
            todo.disabled = 1;
            break;
        case OPT_MISSING_HELP:
            todo.missing_help = 1;
            break;
        case OPT_OBJECTS:
            todo.objects = 1;
            break;
        case OPT_OPTIONS:
            list_options_for_command(opt_arg());
            break;
        case OPT_VERBOSE:
            verbose = 1;
            break;
        }
        done = 1;
    }
    if (opt_num_rest() != 0) {
        BIO_printf(bio_err, "Extra arguments given.\n");
        goto opthelp;
    }

    if (todo.commands)
        list_type(FT_general, one);
    if (todo.digest_commands)
        list_type(FT_md, one);
    if (todo.digest_algorithms)
        list_digests();
    if (todo.kdf_algorithms)
        list_kdfs();
    if (todo.mac_algorithms)
        list_macs();
    if (todo.cipher_commands)
        list_type(FT_cipher, one);
    if (todo.cipher_algorithms)
        list_ciphers();
    if (todo.pk_algorithms)
        list_pkey();
    if (todo.pk_method)
        list_pkey_meth();
    if (todo.engines)
        list_engines();
    if (todo.disabled)
        list_disabled();
    if (todo.missing_help)
        list_missing_help();
    if (todo.objects)
        list_objects();

    if (!done)
        goto opthelp;

    return 0;
}