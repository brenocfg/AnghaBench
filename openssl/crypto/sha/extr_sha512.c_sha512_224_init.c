#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  md_len; scalar_t__ num; scalar_t__ Nh; scalar_t__ Nl; void** h; } ;
typedef  TYPE_1__ SHA512_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA224_DIGEST_LENGTH ; 
 void* U64 (int) ; 

int sha512_224_init(SHA512_CTX *c)
{
    c->h[0] = U64(0x8c3d37c819544da2);
    c->h[1] = U64(0x73e1996689dcd4d6);
    c->h[2] = U64(0x1dfab7ae32ff9c82);
    c->h[3] = U64(0x679dd514582f9fcf);
    c->h[4] = U64(0x0f6d2b697bd44da8);
    c->h[5] = U64(0x77e36f7304c48942);
    c->h[6] = U64(0x3f9d85a86a1d36c8);
    c->h[7] = U64(0x1112e6ad91d692a1);

    c->Nl = 0;
    c->Nh = 0;
    c->num = 0;
    c->md_len = SHA224_DIGEST_LENGTH;
    return 1;
}