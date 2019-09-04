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
struct TYPE_4__ {int nid; } ;
typedef  TYPE_1__ ASN1_STRING_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_nid2ln (int) ; 
 size_t OSSL_NELEM (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_info (char*) ; 
 scalar_t__ TEST_int_ne (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_note (char*,size_t,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* tbl_standard ; 

__attribute__((used)) static int test_tbl_standard(void)
{
    const ASN1_STRING_TABLE *tmp;
    int last_nid = -1;
    size_t i;

    for (tmp = tbl_standard, i = 0; i < OSSL_NELEM(tbl_standard); i++, tmp++) {
        if (tmp->nid < last_nid) {
            last_nid = 0;
            break;
        }
        last_nid = tmp->nid;
    }

    if (TEST_int_ne(last_nid, 0)) {
        TEST_info("asn1 tbl_standard: Table order OK");
        return 1;
    }

    TEST_info("asn1 tbl_standard: out of order");
    for (tmp = tbl_standard, i = 0; i < OSSL_NELEM(tbl_standard); i++, tmp++)
        TEST_note("asn1 tbl_standard: Index %zu, NID %d, Name=%s",
                  i, tmp->nid, OBJ_nid2ln(tmp->nid));

    return 0;
}