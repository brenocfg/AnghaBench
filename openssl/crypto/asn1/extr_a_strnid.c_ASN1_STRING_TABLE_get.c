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
struct TYPE_7__ {int nid; } ;
typedef  TYPE_1__ ASN1_STRING_TABLE ;

/* Variables and functions */
 TYPE_1__* OBJ_bsearch_table (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_CONFIG ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int sk_ASN1_STRING_TABLE_find (scalar_t__,TYPE_1__*) ; 
 TYPE_1__* sk_ASN1_STRING_TABLE_value (scalar_t__,int) ; 
 scalar_t__ stable ; 
 int /*<<< orphan*/  tbl_standard ; 

ASN1_STRING_TABLE *ASN1_STRING_TABLE_get(int nid)
{
    int idx;
    ASN1_STRING_TABLE fnd;

    /* "stable" can be impacted by config, so load the config file first */
    OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CONFIG, NULL);

    fnd.nid = nid;
    if (stable) {
        idx = sk_ASN1_STRING_TABLE_find(stable, &fnd);
        if (idx >= 0)
            return sk_ASN1_STRING_TABLE_value(stable, idx);
    }
    return OBJ_bsearch_table(&fnd, tbl_standard, OSSL_NELEM(tbl_standard));
}