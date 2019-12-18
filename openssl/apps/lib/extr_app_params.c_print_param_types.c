#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int,char*,char const*) ; 
 int /*<<< orphan*/  bio_out ; 
 int /*<<< orphan*/  describe_param_type (char*,int,TYPE_1__ const*) ; 

int print_param_types(const char *thing, const OSSL_PARAM *pdefs, int indent)
{
    if (pdefs == NULL) {
        BIO_printf(bio_out, "%*sNo declared %s\n", indent, "", thing);
    } else if (pdefs->key == NULL) {
        /*
         * An empty list?  This shouldn't happen, but let's just make sure to
         * say something if there's a badly written provider...
         */
        BIO_printf(bio_out, "%*sEmpty list of %s (!!!)\n", indent, "", thing);
    } else {
        BIO_printf(bio_out, "%*s%s:\n", indent, "", thing);
        for (; pdefs->key != NULL; pdefs++) {
            char buf[200];       /* This should be ample space */

            describe_param_type(buf, sizeof(buf), pdefs);
            BIO_printf(bio_out, "%*s  %s\n", indent, "", buf);
        }
    }
    return 1;
}