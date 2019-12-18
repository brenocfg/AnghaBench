#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  block128_f ;
struct TYPE_3__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {TYPE_1__ T; TYPE_1__ C; TYPE_1__ P; TYPE_1__ A; TYPE_1__ IV; TYPE_1__ K; } ;
typedef  TYPE_1__ SIZED_DATA ;
typedef  int /*<<< orphan*/  GCM128_CONTEXT ;
typedef  int /*<<< orphan*/  AES_KEY ;

/* Variables and functions */
 scalar_t__ AES_encrypt ; 
 int /*<<< orphan*/  AES_set_encrypt_key (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_gcm128_aad (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CRYPTO_gcm128_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  CRYPTO_gcm128_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  CRYPTO_gcm128_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CRYPTO_gcm128_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_gcm128_setiv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,int,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* gcm128_vectors ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int test_gcm128(int idx)
{
    unsigned char out[512];
    SIZED_DATA K = gcm128_vectors[idx].K;
    SIZED_DATA IV = gcm128_vectors[idx].IV;
    SIZED_DATA A = gcm128_vectors[idx].A;
    SIZED_DATA P = gcm128_vectors[idx].P;
    SIZED_DATA C = gcm128_vectors[idx].C;
    SIZED_DATA T = gcm128_vectors[idx].T;
    GCM128_CONTEXT ctx;
    AES_KEY key;

    /* Size 1 inputs are special-cased to signal NULL. */
    if (A.size == 1)
        A.data = NULL;
    if (P.size == 1)
        P.data = NULL;
    if (C.size == 1)
        C.data = NULL;

    AES_set_encrypt_key(K.data, K.size * 8, &key);

    CRYPTO_gcm128_init(&ctx, &key, (block128_f)AES_encrypt);
    CRYPTO_gcm128_setiv(&ctx, IV.data, IV.size);
    memset(out, 0, P.size);
    if (A.data != NULL)
        CRYPTO_gcm128_aad(&ctx, A.data, A.size);
    if (P.data != NULL)
        CRYPTO_gcm128_encrypt( &ctx, P.data, out, P.size);
    if (!TEST_false(CRYPTO_gcm128_finish(&ctx, T.data, 16))
            || (C.data != NULL
                    && !TEST_mem_eq(out, P.size, C.data, P.size)))
        return 0;

    CRYPTO_gcm128_setiv(&ctx, IV.data, IV.size);
    memset(out, 0, P.size);
    if (A.data != NULL)
        CRYPTO_gcm128_aad(&ctx, A.data, A.size);
    if (C.data != NULL)
        CRYPTO_gcm128_decrypt(&ctx, C.data, out, P.size);
    if (!TEST_false(CRYPTO_gcm128_finish(&ctx, T.data, 16))
            || (P.data != NULL
                    && !TEST_mem_eq(out, P.size, P.data, P.size)))
        return 0;

    return 1;
}