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
 int /*<<< orphan*/  SHA512_DIGEST_LENGTH ; 
 void* U64 (int) ; 

int SHA512_Init(SHA512_CTX *c)
{
    c->h[0] = U64(0x6a09e667f3bcc908);
    c->h[1] = U64(0xbb67ae8584caa73b);
    c->h[2] = U64(0x3c6ef372fe94f82b);
    c->h[3] = U64(0xa54ff53a5f1d36f1);
    c->h[4] = U64(0x510e527fade682d1);
    c->h[5] = U64(0x9b05688c2b3e6c1f);
    c->h[6] = U64(0x1f83d9abfb41bd6b);
    c->h[7] = U64(0x5be0cd19137e2179);

    c->Nl = 0;
    c->Nh = 0;
    c->num = 0;
    c->md_len = SHA512_DIGEST_LENGTH;
    return 1;
}