#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ encode_expectations_elem_size; int /*<<< orphan*/  asn1_type; } ;
typedef  TYPE_1__ TEST_PACKAGE ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_ITEM_ptr (int /*<<< orphan*/ ) ; 
 int ASN1_item_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ DATA_BUF_SIZE ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (scalar_t__) ; 
 int /*<<< orphan*/  RAND_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/  bio_err ; 

__attribute__((used)) static int do_print_item(const TEST_PACKAGE *package)
{
#define DATA_BUF_SIZE 256
    const ASN1_ITEM *i = ASN1_ITEM_ptr(package->asn1_type);
    ASN1_VALUE *o;
    int ret;

    OPENSSL_assert(package->encode_expectations_elem_size <= DATA_BUF_SIZE);
    if ((o = OPENSSL_malloc(DATA_BUF_SIZE)) == NULL)
        return 0;

    (void)RAND_bytes((unsigned char*)o,
                     (int)package->encode_expectations_elem_size);
    ret = ASN1_item_print(bio_err, o, 0, i, NULL);
    OPENSSL_free(o);

    return ret;
}