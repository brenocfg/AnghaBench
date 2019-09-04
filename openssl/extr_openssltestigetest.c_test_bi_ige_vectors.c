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
struct bi_ige_test {int length; scalar_t__ encrypt; int keysize; int /*<<< orphan*/  in; int /*<<< orphan*/  iv; int /*<<< orphan*/  key2; int /*<<< orphan*/  key1; int /*<<< orphan*/  out; } ;
typedef  int /*<<< orphan*/  AES_KEY ;

/* Variables and functions */
 scalar_t__ AES_ENCRYPT ; 
 int /*<<< orphan*/  AES_bi_ige_encrypt (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AES_set_decrypt_key (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AES_set_encrypt_key (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int MAX_VECTOR_SIZE ; 
 int /*<<< orphan*/  TEST_int_le (int,int) ; 
 int /*<<< orphan*/  TEST_mem_eq (int /*<<< orphan*/ ,int,unsigned char*,int) ; 
 struct bi_ige_test* bi_ige_test_vectors ; 
 int /*<<< orphan*/  test_output_memory (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int test_bi_ige_vectors(int n)
{
    const struct bi_ige_test *const v = &bi_ige_test_vectors[n];
    AES_KEY key1;
    AES_KEY key2;
    unsigned char buf[MAX_VECTOR_SIZE];

        if (!TEST_int_le(v->length, MAX_VECTOR_SIZE))
            return 0;

    if (v->encrypt == AES_ENCRYPT) {
        AES_set_encrypt_key(v->key1, 8 * v->keysize, &key1);
        AES_set_encrypt_key(v->key2, 8 * v->keysize, &key2);
    } else {
        AES_set_decrypt_key(v->key1, 8 * v->keysize, &key1);
        AES_set_decrypt_key(v->key2, 8 * v->keysize, &key2);
    }

    AES_bi_ige_encrypt(v->in, buf, v->length, &key1, &key2, v->iv,
                       v->encrypt);

    if (!TEST_mem_eq(v->out, v->length, buf, v->length)) {
        test_output_memory("key 1", v->key1, sizeof(v->key1));
        test_output_memory("key 2", v->key2, sizeof(v->key2));
        test_output_memory("iv", v->iv, sizeof(v->iv));
        test_output_memory("in", v->in, v->length);
        return 0;
    }

    return 1;
}