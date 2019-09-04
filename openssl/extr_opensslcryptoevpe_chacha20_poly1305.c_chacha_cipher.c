#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  d; } ;
struct TYPE_5__ {unsigned int partial_len; int* buf; unsigned int* counter; TYPE_1__ key; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  TYPE_2__ EVP_CHACHA_KEY ;

/* Variables and functions */
 unsigned int CHACHA_BLK_SIZE ; 
 int /*<<< orphan*/  ChaCha20_ctr32 (unsigned char*,unsigned char const*,unsigned int,int /*<<< orphan*/ ,unsigned int*) ; 
 TYPE_2__* data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int chacha_cipher(EVP_CIPHER_CTX * ctx, unsigned char *out,
                         const unsigned char *inp, size_t len)
{
    EVP_CHACHA_KEY *key = data(ctx);
    unsigned int n, rem, ctr32;

    if ((n = key->partial_len)) {
        while (len && n < CHACHA_BLK_SIZE) {
            *out++ = *inp++ ^ key->buf[n++];
            len--;
        }
        key->partial_len = n;

        if (len == 0)
            return 1;

        if (n == CHACHA_BLK_SIZE) {
            key->partial_len = 0;
            key->counter[0]++;
            if (key->counter[0] == 0)
                key->counter[1]++;
        }
    }

    rem = (unsigned int)(len % CHACHA_BLK_SIZE);
    len -= rem;
    ctr32 = key->counter[0];
    while (len >= CHACHA_BLK_SIZE) {
        size_t blocks = len / CHACHA_BLK_SIZE;
        /*
         * 1<<28 is just a not-so-small yet not-so-large number...
         * Below condition is practically never met, but it has to
         * be checked for code correctness.
         */
        if (sizeof(size_t)>sizeof(unsigned int) && blocks>(1U<<28))
            blocks = (1U<<28);

        /*
         * As ChaCha20_ctr32 operates on 32-bit counter, caller
         * has to handle overflow. 'if' below detects the
         * overflow, which is then handled by limiting the
         * amount of blocks to the exact overflow point...
         */
        ctr32 += (unsigned int)blocks;
        if (ctr32 < blocks) {
            blocks -= ctr32;
            ctr32 = 0;
        }
        blocks *= CHACHA_BLK_SIZE;
        ChaCha20_ctr32(out, inp, blocks, key->key.d, key->counter);
        len -= blocks;
        inp += blocks;
        out += blocks;

        key->counter[0] = ctr32;
        if (ctr32 == 0) key->counter[1]++;
    }

    if (rem) {
        memset(key->buf, 0, sizeof(key->buf));
        ChaCha20_ctr32(key->buf, key->buf, CHACHA_BLK_SIZE,
                       key->key.d, key->counter);
        for (n = 0; n < rem; n++)
            out[n] = inp[n] ^ key->buf[n];
        key->partial_len = rem;
    }

    return 1;
}