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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_lebin2bn (unsigned char const*,int,int /*<<< orphan*/ *) ; 

BIGNUM *BN_native2bn(const unsigned char *s, int len, BIGNUM *ret)
{
#ifdef B_ENDIAN
    return BN_bin2bn(s, len, ret);
#else
    return BN_lebin2bn(s, len, ret);
#endif
}