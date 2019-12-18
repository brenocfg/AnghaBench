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
typedef  int /*<<< orphan*/  CONF ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ENV_OID_FILE ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 char* NCONF_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_create_objects (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_oid_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * app_load_config (char const*) ; 
 int /*<<< orphan*/  bio_err ; 

__attribute__((used)) static CONF *load_config_file(const char *configfile)
{
    CONF *conf = app_load_config(configfile);

    if (conf != NULL) {
        const char *p;

        BIO_printf(bio_err, "Using configuration from %s\n", configfile);
        p = NCONF_get_string(conf, NULL, ENV_OID_FILE);
        if (p != NULL) {
            BIO *oid_bio = BIO_new_file(p, "r");
            if (!oid_bio)
                ERR_print_errors(bio_err);
            else {
                OBJ_create_objects(oid_bio);
                BIO_free_all(oid_bio);
            }
        } else
            ERR_clear_error();
        if (!add_oid_section(conf))
            ERR_print_errors(bio_err);
    }
    return conf;
}