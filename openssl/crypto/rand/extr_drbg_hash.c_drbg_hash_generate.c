#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned char* C; int /*<<< orphan*/  V; } ;
struct TYPE_8__ {TYPE_2__ hash; } ;
struct TYPE_10__ {int reseed_gen_counter; int seedlen; TYPE_1__ data; } ;
typedef  TYPE_2__ RAND_DRBG_HASH ;
typedef  TYPE_3__ RAND_DRBG ;

/* Variables and functions */
 scalar_t__ add_bytes (TYPE_3__*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 scalar_t__ add_hash_to_v (TYPE_3__*,int,unsigned char const*,size_t) ; 
 scalar_t__ hash_gen (TYPE_3__*,unsigned char*,size_t) ; 

__attribute__((used)) static int drbg_hash_generate(RAND_DRBG *drbg,
                              unsigned char *out, size_t outlen,
                              const unsigned char *adin, size_t adin_len)
{
    RAND_DRBG_HASH *hash = &drbg->data.hash;
    unsigned char counter[4];
    int reseed_counter = drbg->reseed_gen_counter;

    counter[0] = (unsigned char)((reseed_counter >> 24) & 0xff);
    counter[1] = (unsigned char)((reseed_counter >> 16) & 0xff);
    counter[2] = (unsigned char)((reseed_counter >> 8) & 0xff);
    counter[3] = (unsigned char)(reseed_counter & 0xff);

    return (adin == NULL
           /* (Step 2) if adin != NULL then V = V + Hash(0x02||V||adin) */
                || adin_len == 0
                || add_hash_to_v(drbg, 0x02, adin, adin_len))
           /* (Step 3) Hashgen(outlen, V) */
           && hash_gen(drbg, out, outlen)
           /* (Step 4/5) H = V = (V + Hash(0x03||V) mod (2^seedlen_bits) */
           && add_hash_to_v(drbg, 0x03, NULL, 0)
           /* (Step 5) V = (V + H + C + reseed_counter) mod (2^seedlen_bits) */
           /* V = (V + C) mod (2^seedlen_bits) */
           && add_bytes(drbg, hash->V, hash->C, drbg->seedlen)
           /* V = (V + reseed_counter) mod (2^seedlen_bits) */
           && add_bytes(drbg, hash->V, counter, 4);
}