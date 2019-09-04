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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  X ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  salsa208_word_specification (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scryptBlockMix(uint32_t *B_, uint32_t *B, uint64_t r)
{
    uint64_t i, j;
    uint32_t X[16], *pB;

    memcpy(X, B + (r * 2 - 1) * 16, sizeof(X));
    pB = B;
    for (i = 0; i < r * 2; i++) {
        for (j = 0; j < 16; j++)
            X[j] ^= *pB++;
        salsa208_word_specification(X);
        memcpy(B_ + (i / 2 + (i & 1) * r) * 16, X, sizeof(X));
    }
    OPENSSL_cleanse(X, sizeof(X));
}