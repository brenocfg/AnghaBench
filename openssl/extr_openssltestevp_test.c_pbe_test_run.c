#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* err; TYPE_1__* data; } ;
struct TYPE_5__ {scalar_t__ pbe_type; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  md; int /*<<< orphan*/  iter; int /*<<< orphan*/  id; int /*<<< orphan*/  salt_len; int /*<<< orphan*/  salt; int /*<<< orphan*/  pass_len; scalar_t__ pass; int /*<<< orphan*/  maxmem; int /*<<< orphan*/  p; int /*<<< orphan*/  r; int /*<<< orphan*/  N; } ;
typedef  TYPE_1__ PBE_DATA ;
typedef  TYPE_2__ EVP_TEST ;

/* Variables and functions */
 scalar_t__ EVP_PBE_scrypt (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ PBE_TYPE_PBKDF2 ; 
 scalar_t__ PBE_TYPE_PKCS12 ; 
 scalar_t__ PBE_TYPE_SCRYPT ; 
 scalar_t__ PKCS12_key_gen_uni (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ PKCS5_PBKDF2_HMAC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 
 int /*<<< orphan*/  memory_err_compare (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pbe_test_run(EVP_TEST *t)
{
    PBE_DATA *expected = t->data;
    unsigned char *key;

    if (!TEST_ptr(key = OPENSSL_malloc(expected->key_len))) {
        t->err = "INTERNAL_ERROR";
        goto err;
    }
    if (expected->pbe_type == PBE_TYPE_PBKDF2) {
        if (PKCS5_PBKDF2_HMAC((char *)expected->pass, expected->pass_len,
                              expected->salt, expected->salt_len,
                              expected->iter, expected->md,
                              expected->key_len, key) == 0) {
            t->err = "PBKDF2_ERROR";
            goto err;
        }
#ifndef OPENSSL_NO_SCRYPT
    } else if (expected->pbe_type == PBE_TYPE_SCRYPT) {
        if (EVP_PBE_scrypt((const char *)expected->pass, expected->pass_len,
                           expected->salt, expected->salt_len, expected->N,
                           expected->r, expected->p, expected->maxmem,
                           key, expected->key_len) == 0) {
            t->err = "SCRYPT_ERROR";
            goto err;
        }
#endif
    } else if (expected->pbe_type == PBE_TYPE_PKCS12) {
        if (PKCS12_key_gen_uni(expected->pass, expected->pass_len,
                               expected->salt, expected->salt_len,
                               expected->id, expected->iter, expected->key_len,
                               key, expected->md) == 0) {
            t->err = "PKCS12_ERROR";
            goto err;
        }
    }
    if (!memory_err_compare(t, "KEY_MISMATCH", expected->key, expected->key_len,
                            key, expected->key_len))
        goto err;

    t->err = NULL;
err:
    OPENSSL_free(key);
    return 1;
}