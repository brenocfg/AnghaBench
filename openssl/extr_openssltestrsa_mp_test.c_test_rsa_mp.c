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
typedef  int /*<<< orphan*/  ptext_ex ;
typedef  int /*<<< orphan*/  RSA ;

/* Variables and functions */
 int /*<<< orphan*/  RSA_PKCS1_PADDING ; 
 int /*<<< orphan*/  RSA_check_key_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new () ; 
 int RSA_private_decrypt (int,unsigned char*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RSA_public_encrypt (int,unsigned char*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int key2048p3 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_rsa_mp(void)
{
    int ret = 0;
    RSA *key;
    unsigned char ptext[256];
    unsigned char ctext[256];
    static unsigned char ptext_ex[] = "\x54\x85\x9b\x34\x2c\x49\xea\x2a";
    int plen;
    int clen = 0;
    int num;

    plen = sizeof(ptext_ex) - 1;
    key = RSA_new();
    if (!TEST_ptr(key))
        goto err;
    clen = key2048p3(key);
    if (!TEST_int_eq(clen, 256))
        goto err;

    if (!TEST_true(RSA_check_key_ex(key, NULL)))
        goto err;

    num = RSA_public_encrypt(plen, ptext_ex, ctext, key,
                             RSA_PKCS1_PADDING);
    if (!TEST_int_eq(num, clen))
        goto err;

    num = RSA_private_decrypt(num, ctext, ptext, key, RSA_PKCS1_PADDING);
    if (!TEST_mem_eq(ptext, num, ptext_ex, plen))
        goto err;

    ret = 1;
err:
    RSA_free(key);
    return ret;
}