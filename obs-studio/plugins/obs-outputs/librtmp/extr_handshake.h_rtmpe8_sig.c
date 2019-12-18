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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int** rtmpe8_keys ; 

__attribute__((used)) static void rtmpe8_sig(uint8_t *in, uint8_t *out, int keyid)
{
    unsigned int i, num_rounds = 32;
    uint32_t v0, v1, sum=0, delta=0x9E3779B9;
    uint32_t const *k;

    v0 = in[0] | (in[1] << 8) | (in[2] << 16) | (in[3] << 24);
    v1 = in[4] | (in[5] << 8) | (in[6] << 16) | (in[7] << 24);
    k = rtmpe8_keys[keyid];

    for (i=0; i < num_rounds; i++)
    {
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
        sum += delta;
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum>>11) & 3]);
    }

    out[0] = v0;
    v0 >>= 8;
    out[1] = v0;
    v0 >>= 8;
    out[2] = v0;
    v0 >>= 8;
    out[3] = v0;

    out[4] = v1;
    v1 >>= 8;
    out[5] = v1;
    v1 >>= 8;
    out[6] = v1;
    v1 >>= 8;
    out[7] = v1;
}