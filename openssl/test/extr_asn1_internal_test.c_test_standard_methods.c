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
struct TYPE_4__ {int pkey_id; int pkey_flags; int /*<<< orphan*/ * pem_str; } ;
typedef  TYPE_1__ EVP_PKEY_ASN1_METHOD ;

/* Variables and functions */
 int ASN1_PKEY_ALIAS ; 
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 size_t OSSL_NELEM (TYPE_1__**) ; 
 int /*<<< orphan*/  TEST_info (char*) ; 
 scalar_t__ TEST_int_ne (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_note (char*,...) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 TYPE_1__** standard_methods ; 

__attribute__((used)) static int test_standard_methods(void)
{
    const EVP_PKEY_ASN1_METHOD **tmp;
    int last_pkey_id = -1;
    size_t i;
    int ok = 1;

    for (tmp = standard_methods, i = 0; i < OSSL_NELEM(standard_methods);
         i++, tmp++) {
        if ((*tmp)->pkey_id < last_pkey_id) {
            last_pkey_id = 0;
            break;
        }
        last_pkey_id = (*tmp)->pkey_id;

        /*
         * One of the following must be true:
         *
         * pem_str == NULL AND ASN1_PKEY_ALIAS is set
         * pem_str != NULL AND ASN1_PKEY_ALIAS is clear
         *
         * Anything else is an error and may lead to a corrupt ASN1 method table
         */
        if (!TEST_true(((*tmp)->pem_str == NULL && ((*tmp)->pkey_flags & ASN1_PKEY_ALIAS) != 0)
                       || ((*tmp)->pem_str != NULL && ((*tmp)->pkey_flags & ASN1_PKEY_ALIAS) == 0))) {
            TEST_note("asn1 standard methods: Index %zu, pkey ID %d, Name=%s",
                      i, (*tmp)->pkey_id, OBJ_nid2sn((*tmp)->pkey_id));
            ok = 0;
        }
    }

    if (TEST_int_ne(last_pkey_id, 0)) {
        TEST_info("asn1 standard methods: Table order OK");
        return ok;
    }

    TEST_note("asn1 standard methods: out of order");
    for (tmp = standard_methods, i = 0; i < OSSL_NELEM(standard_methods);
         i++, tmp++)
        TEST_note("asn1 standard methods: Index %zu, pkey ID %d, Name=%s",
                  i, (*tmp)->pkey_id, OBJ_nid2sn((*tmp)->pkey_id));

    return 0;
}