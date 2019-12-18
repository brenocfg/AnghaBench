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
 int BN_hex2bn (int /*<<< orphan*/ **,char const*) ; 

__attribute__((used)) static int parseBN(BIGNUM **out, const char *in)
{
    *out = NULL;
    return BN_hex2bn(out, in);
}