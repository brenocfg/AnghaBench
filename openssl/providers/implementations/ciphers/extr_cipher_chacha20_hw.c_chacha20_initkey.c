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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/ * d; } ;
struct TYPE_4__ {scalar_t__ partial_len; TYPE_1__ key; } ;
typedef  int /*<<< orphan*/  PROV_CIPHER_CTX ;
typedef  TYPE_2__ PROV_CHACHA20_CTX ;

/* Variables and functions */
 unsigned int CHACHA_KEY_SIZE ; 
 int /*<<< orphan*/  CHACHA_U8TOU32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int chacha20_initkey(PROV_CIPHER_CTX *bctx, const uint8_t *key,
                            size_t keylen)
{
    PROV_CHACHA20_CTX *ctx = (PROV_CHACHA20_CTX *)bctx;
    unsigned int i;

    if (key != NULL) {
        for (i = 0; i < CHACHA_KEY_SIZE; i += 4)
            ctx->key.d[i / 4] = CHACHA_U8TOU32(key + i);
    }
    ctx->partial_len = 0;
    return 1;
}