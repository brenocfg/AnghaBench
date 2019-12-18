#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_9__ {TYPE_1__* recipient; } ;
struct TYPE_8__ {TYPE_4__* hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  directoryName; } ;
struct TYPE_6__ {TYPE_2__ d; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ CMP_HDR_TEST_FIXTURE ;

/* Variables and functions */
 int GEN_DIRNAME ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_NAME_ADD (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  X509_NAME_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_NAME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_NAME_new () ; 
 int /*<<< orphan*/  ossl_cmp_hdr_set1_recipient (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int execute_HDR_set1_recipient_test(CMP_HDR_TEST_FIXTURE *fixture)
{
    X509_NAME *x509name = X509_NAME_new();

    if (!TEST_ptr(x509name))
        return 0;

    X509_NAME_ADD(x509name, "CN", "A common recipient name");
    if (!TEST_int_eq(ossl_cmp_hdr_set1_recipient(fixture->hdr, x509name), 1))
        return 0;

    if (!TEST_int_eq(fixture->hdr->recipient->type, GEN_DIRNAME))
        return 0;

    if (!TEST_int_eq(
            X509_NAME_cmp(fixture->hdr->recipient->d.directoryName, x509name),0))
        return 0;

    X509_NAME_free(x509name);
    return 1;
}