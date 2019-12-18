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
struct TYPE_2__ {int /*<<< orphan*/ * outw; int /*<<< orphan*/ * inw; int /*<<< orphan*/  ks; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 int /*<<< orphan*/  DES_set_key_unchecked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,int) ; 

__attribute__((used)) static int desx_cbc_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
                             const unsigned char *iv, int enc)
{
    DES_cblock *deskey = (DES_cblock *)key;

    DES_set_key_unchecked(deskey, &data(ctx)->ks);
    memcpy(&data(ctx)->inw[0], &key[8], 8);
    memcpy(&data(ctx)->outw[0], &key[16], 8);

    return 1;
}