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
typedef  int BN_ULONG ;

/* Variables and functions */
 int BN_BITS2 ; 

__attribute__((used)) static BN_ULONG is_zero(BN_ULONG in)
{
    in |= (0 - in);
    in = ~in;
    in >>= BN_BITS2 - 1;
    return in;
}