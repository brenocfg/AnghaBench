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
 int /*<<< orphan*/  cipher_hw_generic_cfb8 (int /*<<< orphan*/ *,unsigned char*,unsigned char const*,size_t) ; 

int cipher_hw_chunked_cfb8(PROV_CIPHER_CTX *ctx, unsigned char *out,
                           const unsigned char *in, size_t inl)
{
    size_t chunk = MAXCHUNK;

    if (inl < chunk)
        chunk = inl;
    while (inl > 0 && inl >= chunk) {
        cipher_hw_generic_cfb8(ctx, out, in, inl);
        inl -= chunk;
        in += chunk;
        out += chunk;
        if (inl < chunk)
            chunk = inl;
    }
    return 1;
}