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
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCONF_default () ; 
 scalar_t__ NCONF_load (int /*<<< orphan*/ *,char*,long*) ; 
 int /*<<< orphan*/ * NCONF_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  collect_all_sections (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_section (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  section_names ; 
 int /*<<< orphan*/  sk_OPENSSL_CSTRING_free (int /*<<< orphan*/ ) ; 
 int sk_OPENSSL_CSTRING_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_OPENSSL_CSTRING_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
    long eline;
    CONF *conf;

    if ((conf = NCONF_new(NCONF_default())) != NULL
        && NCONF_load(conf, argv[1], &eline)) {
        int i;

        collect_all_sections(conf);
        for (i = 0; i < sk_OPENSSL_CSTRING_num(section_names); i++) {
            dump_section(sk_OPENSSL_CSTRING_value(section_names, i), conf);
        }
        sk_OPENSSL_CSTRING_free(section_names);
    } else {
        ERR_print_errors_fp(stderr);
        return 1;
    }
    return 0;
}