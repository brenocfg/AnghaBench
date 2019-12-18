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
typedef  int /*<<< orphan*/  PROV_CIPHER_CTX ;

/* Variables and functions */
 size_t MAXCHUNK ; 
 int /*<<< orphan*/  cipher_hw_generic_ofb128 (int /*<<< orphan*/ *,unsigned char*,unsigned char const*,size_t) ; 

int cipher_hw_chunked_ofb128(PROV_CIPHER_CTX *ctx, unsigned char *out,
                             const unsigned char *in, size_t inl)
{
    while (inl >= MAXCHUNK) {
        cipher_hw_generic_ofb128(ctx, out, in, MAXCHUNK);
        inl -= MAXCHUNK;
        in  += MAXCHUNK;
        out += MAXCHUNK;
    }
    if (inl > 0)
        cipher_hw_generic_ofb128(ctx, out, in, inl);
    return 1;
}