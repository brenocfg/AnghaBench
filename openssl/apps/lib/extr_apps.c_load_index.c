#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int unique_subject; } ;
struct TYPE_7__ {struct stat dbst; int /*<<< orphan*/  dbfname; TYPE_1__ attributes; int /*<<< orphan*/ * db; } ;
typedef  int /*<<< orphan*/  TXT_DB ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ DB_ATTR ;
typedef  int /*<<< orphan*/  CONF ;
typedef  TYPE_2__ CA_DB ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_get_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,char const*) ; 
 int BSIZE ; 
 int /*<<< orphan*/  DB_NUMBER ; 
 int /*<<< orphan*/  ERR_LIB_SYS ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_raise_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  NCONF_free (int /*<<< orphan*/ *) ; 
 char* NCONF_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  OPENSSL_strdup (char const*) ; 
 int /*<<< orphan*/  TXT_DB_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TXT_DB_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * app_load_config_quiet (char*) ; 
 TYPE_2__* app_malloc (int,char*) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int parse_yesno (char*,int) ; 

CA_DB *load_index(const char *dbfile, DB_ATTR *db_attr)
{
    CA_DB *retdb = NULL;
    TXT_DB *tmpdb = NULL;
    BIO *in;
    CONF *dbattr_conf = NULL;
    char buf[BSIZE];
#ifndef OPENSSL_NO_POSIX_IO
    FILE *dbfp;
    struct stat dbst;
#endif

    in = BIO_new_file(dbfile, "r");
    if (in == NULL) {
        ERR_print_errors(bio_err);
        goto err;
    }

#ifndef OPENSSL_NO_POSIX_IO
    BIO_get_fp(in, &dbfp);
    if (fstat(fileno(dbfp), &dbst) == -1) {
        ERR_raise_data(ERR_LIB_SYS, errno,
                       "calling fstat(%s)", dbfile);
        ERR_print_errors(bio_err);
        goto err;
    }
#endif

    if ((tmpdb = TXT_DB_read(in, DB_NUMBER)) == NULL)
        goto err;

#ifndef OPENSSL_SYS_VMS
    BIO_snprintf(buf, sizeof(buf), "%s.attr", dbfile);
#else
    BIO_snprintf(buf, sizeof(buf), "%s-attr", dbfile);
#endif
    dbattr_conf = app_load_config_quiet(buf);

    retdb = app_malloc(sizeof(*retdb), "new DB");
    retdb->db = tmpdb;
    tmpdb = NULL;
    if (db_attr)
        retdb->attributes = *db_attr;
    else {
        retdb->attributes.unique_subject = 1;
    }

    if (dbattr_conf) {
        char *p = NCONF_get_string(dbattr_conf, NULL, "unique_subject");
        if (p) {
            retdb->attributes.unique_subject = parse_yesno(p, 1);
        }
    }

    retdb->dbfname = OPENSSL_strdup(dbfile);
#ifndef OPENSSL_NO_POSIX_IO
    retdb->dbst = dbst;
#endif

 err:
    NCONF_free(dbattr_conf);
    TXT_DB_free(tmpdb);
    BIO_free_all(in);
    return retdb;
}