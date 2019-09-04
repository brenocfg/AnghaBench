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
typedef  scalar_t__ zero ;
typedef  scalar_t__ two225m97p2 ;
typedef  scalar_t__ two224m96p1 ;
typedef  int limb ;
typedef  int int64_t ;
typedef  int* felem ;

/* Variables and functions */

__attribute__((used)) static limb felem_is_zero(const felem in)
{
    limb zero, two224m96p1, two225m97p2;

    zero = in[0] | in[1] | in[2] | in[3];
    zero = (((int64_t) (zero) - 1) >> 63) & 1;
    two224m96p1 = (in[0] ^ 1) | (in[1] ^ 0x00ffff0000000000)
        | (in[2] ^ 0x00ffffffffffffff) | (in[3] ^ 0x00ffffffffffffff);
    two224m96p1 = (((int64_t) (two224m96p1) - 1) >> 63) & 1;
    two225m97p2 = (in[0] ^ 2) | (in[1] ^ 0x00fffe0000000000)
        | (in[2] ^ 0x00ffffffffffffff) | (in[3] ^ 0x01ffffffffffffff);
    two225m97p2 = (((int64_t) (two225m97p2) - 1) >> 63) & 1;
    return (zero | two224m96p1 | two225m97p2);
}