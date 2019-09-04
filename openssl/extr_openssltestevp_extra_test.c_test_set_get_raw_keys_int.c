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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * priv; int /*<<< orphan*/ * pub; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_get_raw_private_key (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 int EVP_PKEY_get_raw_public_key (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 int /*<<< orphan*/ * EVP_PKEY_new_raw_private_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/ * EVP_PKEY_new_raw_public_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,size_t,unsigned char*,size_t) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 TYPE_1__* keys ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_set_get_raw_keys_int(int tst, int pub)
{
    int ret = 0;
    unsigned char buf[80];
    unsigned char *in;
    size_t inlen, len = 0;
    EVP_PKEY *pkey;

    /* Check if this algorithm supports public keys */
    if (keys[tst].pub == NULL)
        return 1;

    memset(buf, 0, sizeof(buf));

    if (pub) {
        inlen = strlen(keys[tst].pub);
        in = (unsigned char *)keys[tst].pub;
        pkey = EVP_PKEY_new_raw_public_key(keys[tst].type,
                                           NULL,
                                           in,
                                           inlen);
    } else {
        inlen = strlen(keys[tst].priv);
        in = (unsigned char *)keys[tst].priv;
        pkey = EVP_PKEY_new_raw_private_key(keys[tst].type,
                                            NULL,
                                            in,
                                            inlen);
    }

    if (!TEST_ptr(pkey)
            || (!pub && !TEST_true(EVP_PKEY_get_raw_private_key(pkey, NULL, &len)))
            || (pub && !TEST_true(EVP_PKEY_get_raw_public_key(pkey, NULL, &len)))
            || !TEST_true(len == inlen)
            || (!pub && !TEST_true(EVP_PKEY_get_raw_private_key(pkey, buf, &len)))
            || (pub && !TEST_true(EVP_PKEY_get_raw_public_key(pkey, buf, &len)))
            || !TEST_mem_eq(in, inlen, buf, len))
        goto done;

    ret = 1;
 done:
    EVP_PKEY_free(pkey);
    return ret;
}