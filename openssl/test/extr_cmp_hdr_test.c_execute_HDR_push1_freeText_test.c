#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  freeText; } ;
struct TYPE_4__ {TYPE_2__* hdr; } ;
typedef  TYPE_1__ CMP_HDR_TEST_FIXTURE ;
typedef  int /*<<< orphan*/  ASN1_UTF8STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_STRING_set (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ASN1_UTF8STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_UTF8STRING_new () ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_cmp_hdr_push1_freeText (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_ASN1_UTF8STRING_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int execute_HDR_push1_freeText_test(CMP_HDR_TEST_FIXTURE *fixture)
{
    ASN1_UTF8STRING* text = ASN1_UTF8STRING_new();

    if (!TEST_ptr(text))
        return 0;

    if (!ASN1_STRING_set(text, "A free text", -1))
        return 0;

    if (!TEST_int_eq(
            ossl_cmp_hdr_push1_freeText(fixture->hdr, text), 1))
        return 0;
    if (!TEST_int_eq(ASN1_STRING_cmp(
            sk_ASN1_UTF8STRING_value(fixture->hdr->freeText, 0), text), 0))
        return 0;

    ASN1_UTF8STRING_free(text);
    return 1;
}