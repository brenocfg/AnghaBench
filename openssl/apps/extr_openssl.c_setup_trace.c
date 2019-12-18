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

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char const*) ; 
 int OSSL_TRACE_CATEGORY_ALL ; 
 int OSSL_TRACE_CATEGORY_NUM ; 
 int OSSL_trace_get_category_num (char*) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_trace ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  setup_trace_category (int) ; 
 int /*<<< orphan*/  sk_tracedata_new_null () ; 
 int /*<<< orphan*/  stderr ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  trace_data_stack ; 

__attribute__((used)) static void setup_trace(const char *str)
{
    char *val;

    /*
     * We add this handler as early as possible to ensure it's executed
     * as late as possible, i.e. after the TRACE code has done its cleanup
     * (which happens last in OPENSSL_cleanup).
     */
    atexit(cleanup_trace);

    trace_data_stack = sk_tracedata_new_null();
    val = OPENSSL_strdup(str);

    if (val != NULL) {
        char *valp = val;
        char *item;

        for (valp = val; (item = strtok(valp, ",")) != NULL; valp = NULL) {
            int category = OSSL_trace_get_category_num(item);

            if (category == OSSL_TRACE_CATEGORY_ALL) {
                while (++category < OSSL_TRACE_CATEGORY_NUM)
                    setup_trace_category(category);
                break;
            } else if (category > 0) {
                setup_trace_category(category);
            } else {
                fprintf(stderr,
                        "warning: unknown trace category: '%s'.\n", item);
            }
        }
    }

    OPENSSL_free(val);
}