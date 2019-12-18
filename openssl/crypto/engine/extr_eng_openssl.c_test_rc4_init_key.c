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
struct TYPE_2__ {int /*<<< orphan*/ * key; int /*<<< orphan*/  ks; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int EVP_CIPHER_CTX_key_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,int const) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__* test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_rc4_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
                             const unsigned char *iv, int enc)
{
    const int n = EVP_CIPHER_CTX_key_length(ctx);

# ifdef TEST_ENG_OPENSSL_RC4_P_INIT
    fprintf(stderr, "(TEST_ENG_OPENSSL_RC4) test_init_key() called\n");
# endif
    if (n <= 0)
        return n;
    memcpy(&test(ctx)->key[0], key, n);
    RC4_set_key(&test(ctx)->ks, n, test(ctx)->key);
    return 1;
}