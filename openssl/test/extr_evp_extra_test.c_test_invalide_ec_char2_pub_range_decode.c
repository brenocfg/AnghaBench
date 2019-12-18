#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ valid; int /*<<< orphan*/  len; int /*<<< orphan*/  der; } ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_mem_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_ptr_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_EC_PUBKEY_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* ec_der_pub_keys ; 

__attribute__((used)) static int test_invalide_ec_char2_pub_range_decode(int id)
{
    int ret = 0;
    BIO *bio = NULL;
    EC_KEY *eckey = NULL;

    if (!TEST_ptr(bio = BIO_new_mem_buf(ec_der_pub_keys[id].der,
                                        ec_der_pub_keys[id].len)))
        goto err;
    eckey = d2i_EC_PUBKEY_bio(bio, NULL);
    ret = (ec_der_pub_keys[id].valid && TEST_ptr(eckey))
          || TEST_ptr_null(eckey);
err:
    EC_KEY_free(eckey);
    BIO_free(bio);
    return ret;
}