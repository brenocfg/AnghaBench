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

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 char* NCONF_get_string (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/ * OPENSSL_strdup (char const*) ; 
 scalar_t__ RAND_load_file (char const*,int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * save_rand_file ; 

void app_RAND_load_conf(CONF *c, const char *section)
{
    const char *randfile = NCONF_get_string(c, section, "RANDFILE");

    if (randfile == NULL) {
        ERR_clear_error();
        return;
    }
    if (RAND_load_file(randfile, -1) < 0) {
        BIO_printf(bio_err, "Can't load %s into RNG\n", randfile);
        ERR_print_errors(bio_err);
    }
    if (save_rand_file == NULL)
        save_rand_file = OPENSSL_strdup(randfile);
}