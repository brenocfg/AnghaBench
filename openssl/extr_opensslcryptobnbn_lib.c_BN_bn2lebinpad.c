#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* d; } ;
typedef  int BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int BN_BYTES ; 
 int BN_num_bytes (TYPE_1__ const*) ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__ const*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

int BN_bn2lebinpad(const BIGNUM *a, unsigned char *to, int tolen)
{
    int i;
    BN_ULONG l;
    bn_check_top(a);
    i = BN_num_bytes(a);
    if (tolen < i)
        return -1;
    /* Add trailing zeroes if necessary */
    if (tolen > i)
        memset(to + i, 0, tolen - i);
    to += i;
    while (i--) {
        l = a->d[i / BN_BYTES];
        to--;
        *to = (unsigned char)(l >> (8 * (i % BN_BYTES))) & 0xff;
    }
    return tolen;
}