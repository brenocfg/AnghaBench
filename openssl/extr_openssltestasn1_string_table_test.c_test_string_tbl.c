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
typedef  int /*<<< orphan*/  ASN1_STRING_TABLE ;

/* Variables and functions */
 int ASN1_STRING_TABLE_add (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_STRING_TABLE_cleanup () ; 
 int /*<<< orphan*/ * ASN1_STRING_TABLE_get (int) ; 
 int /*<<< orphan*/  MBSTRING_ASC ; 
 int /*<<< orphan*/  TEST_info (char*,...) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_ptr_null (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_true (int) ; 

__attribute__((used)) static int test_string_tbl(void)
{
    const ASN1_STRING_TABLE *tmp = NULL;
    int nid = 12345678, nid2 = 87654321, rv = 0, ret = 0;

    tmp = ASN1_STRING_TABLE_get(nid);
    if (!TEST_ptr_null(tmp)) {
        TEST_info("asn1 string table: ASN1_STRING_TABLE_get non-exist nid");
        goto out;
    }

    ret = ASN1_STRING_TABLE_add(nid, -1, -1, MBSTRING_ASC, 0);
    if (!TEST_true(ret)) {
        TEST_info("asn1 string table: add NID(%d) failed", nid);
        goto out;
    }

    ret = ASN1_STRING_TABLE_add(nid2, -1, -1, MBSTRING_ASC, 0);
    if (!TEST_true(ret)) {
        TEST_info("asn1 string table: add NID(%d) failed", nid2);
        goto out;
    }

    tmp = ASN1_STRING_TABLE_get(nid);
    if (!TEST_ptr(tmp)) {
        TEST_info("asn1 string table: get NID(%d) failed", nid);
        goto out;
    }

    tmp = ASN1_STRING_TABLE_get(nid2);
    if (!TEST_ptr(tmp)) {
        TEST_info("asn1 string table: get NID(%d) failed", nid2);
        goto out;
    }

    ASN1_STRING_TABLE_cleanup();

    /* check if all newly added NIDs are cleaned up */
    tmp = ASN1_STRING_TABLE_get(nid);
    if (!TEST_ptr_null(tmp)) {
        TEST_info("asn1 string table: get NID(%d) failed", nid);
        goto out;
    }

    tmp = ASN1_STRING_TABLE_get(nid2);
    if (!TEST_ptr_null(tmp)) {
        TEST_info("asn1 string table: get NID(%d) failed", nid2);
        goto out;
    }

    rv = 1;
 out:
    return rv;
}