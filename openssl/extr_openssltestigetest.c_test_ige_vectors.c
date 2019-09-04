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
struct ige_test {int length; scalar_t__ encrypt; unsigned char* key; unsigned char* iv; unsigned char* in; int /*<<< orphan*/  out; } ;
typedef  int /*<<< orphan*/  iv ;
typedef  int /*<<< orphan*/  AES_KEY ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 scalar_t__ AES_ENCRYPT ; 
 int /*<<< orphan*/  AES_ige_encrypt (unsigned char*,unsigned char*,int,int /*<<< orphan*/ *,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  AES_set_decrypt_key (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AES_set_encrypt_key (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int MAX_VECTOR_SIZE ; 
 int /*<<< orphan*/  TEST_info (char*,int) ; 
 int /*<<< orphan*/  TEST_int_le (int,int) ; 
 int /*<<< orphan*/  TEST_mem_eq (int /*<<< orphan*/ ,int,unsigned char*,int) ; 
 struct ige_test* ige_test_vectors ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  test_output_memory (char*,unsigned char*,int) ; 

__attribute__((used)) static int test_ige_vectors(int n)
{
    const struct ige_test *const v = &ige_test_vectors[n];
    AES_KEY key;
    unsigned char buf[MAX_VECTOR_SIZE];
    unsigned char iv[AES_BLOCK_SIZE * 2];
    int testresult = 1;

    if (!TEST_int_le(v->length, MAX_VECTOR_SIZE))
        return 0;

    if (v->encrypt == AES_ENCRYPT)
        AES_set_encrypt_key(v->key, 8 * sizeof(v->key), &key);
    else
        AES_set_decrypt_key(v->key, 8 * sizeof(v->key), &key);
    memcpy(iv, v->iv, sizeof(iv));
    AES_ige_encrypt(v->in, buf, v->length, &key, iv, v->encrypt);

    if (!TEST_mem_eq(v->out, v->length, buf, v->length)) {
        TEST_info("IGE test vector %d failed", n);
        test_output_memory("key", v->key, sizeof(v->key));
        test_output_memory("iv", v->iv, sizeof(v->iv));
        test_output_memory("in", v->in, v->length);
        testresult = 0;
    }

    /* try with in == out */
    memcpy(iv, v->iv, sizeof(iv));
    memcpy(buf, v->in, v->length);
    AES_ige_encrypt(buf, buf, v->length, &key, iv, v->encrypt);

    if (!TEST_mem_eq(v->out, v->length, buf, v->length)) {
        TEST_info("IGE test vector %d failed (with in == out)", n);
        test_output_memory("key", v->key, sizeof(v->key));
        test_output_memory("iv", v->iv, sizeof(v->iv));
        test_output_memory("in", v->in, v->length);
        testresult = 0;
    }

    return testresult;
}