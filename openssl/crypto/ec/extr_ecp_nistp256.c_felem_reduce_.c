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
typedef  int* longfelem ;
typedef  int int128_t ;
typedef  int* felem ;

/* Variables and functions */

__attribute__((used)) static void felem_reduce_(felem out, const longfelem in)
{
    int128_t c;
    /* combine common terms from below */
    c = in[4] + (in[5] << 32);
    out[0] += c;
    out[3] -= c;

    c = in[5] - in[7];
    out[1] += c;
    out[2] -= c;

    /* the remaining terms */
    /* 256: [(0,1),(96,-1),(192,-1),(224,1)] */
    out[1] -= (in[4] << 32);
    out[3] += (in[4] << 32);

    /* 320: [(32,1),(64,1),(128,-1),(160,-1),(224,-1)] */
    out[2] -= (in[5] << 32);

    /* 384: [(0,-1),(32,-1),(96,2),(128,2),(224,-1)] */
    out[0] -= in[6];
    out[0] -= (in[6] << 32);
    out[1] += (in[6] << 33);
    out[2] += (in[6] * 2);
    out[3] -= (in[6] << 32);

    /* 448: [(0,-1),(32,-1),(64,-1),(128,1),(160,2),(192,3)] */
    out[0] -= in[7];
    out[0] -= (in[7] << 32);
    out[2] += (in[7] << 33);
    out[3] += (in[7] * 3);
}