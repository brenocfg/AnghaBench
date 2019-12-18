#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* h; int /*<<< orphan*/  md_len; } ;
typedef  TYPE_1__ SHA256_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA224_DIGEST_LENGTH ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int SHA224_Init(SHA256_CTX *c)
{
    memset(c, 0, sizeof(*c));
    c->h[0] = 0xc1059ed8UL;
    c->h[1] = 0x367cd507UL;
    c->h[2] = 0x3070dd17UL;
    c->h[3] = 0xf70e5939UL;
    c->h[4] = 0xffc00b31UL;
    c->h[5] = 0x68581511UL;
    c->h[6] = 0x64f98fa7UL;
    c->h[7] = 0xbefa4fa4UL;
    c->md_len = SHA224_DIGEST_LENGTH;
    return 1;
}