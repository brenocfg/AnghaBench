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
struct TYPE_3__ {unsigned char* kder; size_t size; int evptype; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_1__ APK_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr_eq (unsigned char const*,unsigned char const*) ; 
 int /*<<< orphan*/ * d2i_AutoPrivateKey (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 TYPE_1__* keydata ; 

__attribute__((used)) static int test_d2i_AutoPrivateKey(int i)
{
    int ret = 0;
    const unsigned char *p;
    EVP_PKEY *pkey = NULL;
    const APK_DATA *ak = &keydata[i];
    const unsigned char *input = ak->kder;
    size_t input_len = ak->size;
    int expected_id = ak->evptype;

    p = input;
    if (!TEST_ptr(pkey = d2i_AutoPrivateKey(NULL, &p, input_len))
            || !TEST_ptr_eq(p, input + input_len)
            || !TEST_int_eq(EVP_PKEY_id(pkey), expected_id))
        goto done;

    ret = 1;

 done:
    EVP_PKEY_free(pkey);
    return ret;
}