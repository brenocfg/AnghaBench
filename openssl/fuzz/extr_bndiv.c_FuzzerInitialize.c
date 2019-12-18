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

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_new () ; 
 void* BN_new () ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_CRYPTO_STRINGS ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* b1 ; 
 void* b2 ; 
 void* b3 ; 
 void* b4 ; 
 void* b5 ; 
 int /*<<< orphan*/  ctx ; 

int FuzzerInitialize(int *argc, char ***argv)
{
    b1 = BN_new();
    b2 = BN_new();
    b3 = BN_new();
    b4 = BN_new();
    b5 = BN_new();
    ctx = BN_CTX_new();

    OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CRYPTO_STRINGS, NULL);
    ERR_clear_error();

    return 1;
}