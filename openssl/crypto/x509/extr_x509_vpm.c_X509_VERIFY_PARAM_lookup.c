#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; } ;
typedef  TYPE_1__ X509_VERIFY_PARAM ;

/* Variables and functions */
 TYPE_1__ const* OBJ_bsearch_table (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_table ; 
 int /*<<< orphan*/ * param_table ; 
 int sk_X509_VERIFY_PARAM_find (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__ const* sk_X509_VERIFY_PARAM_value (int /*<<< orphan*/ *,int) ; 

const X509_VERIFY_PARAM *X509_VERIFY_PARAM_lookup(const char *name)
{
    int idx;
    X509_VERIFY_PARAM pm;

    pm.name = (char *)name;
    if (param_table != NULL) {
        idx = sk_X509_VERIFY_PARAM_find(param_table, &pm);
        if (idx >= 0)
            return sk_X509_VERIFY_PARAM_value(param_table, idx);
    }
    return OBJ_bsearch_table(&pm, default_table, OSSL_NELEM(default_table));
}