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
struct TYPE_2__ {int /*<<< orphan*/  rounds; int /*<<< orphan*/  ks; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int EVP_CIPHER_CTX_key_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_F_R_32_12_16_INIT_KEY ; 
 int /*<<< orphan*/  EVP_R_BAD_KEY_LENGTH ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RC5_32_set_key (int /*<<< orphan*/ *,int,unsigned char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r_32_12_16_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
                               const unsigned char *iv, int enc)
{
    if (EVP_CIPHER_CTX_key_length(ctx) > 255) {
        EVPerr(EVP_F_R_32_12_16_INIT_KEY, EVP_R_BAD_KEY_LENGTH);
        return 0;
    }
    return RC5_32_set_key(&data(ctx)->ks, EVP_CIPHER_CTX_key_length(ctx),
                          key, data(ctx)->rounds);
}