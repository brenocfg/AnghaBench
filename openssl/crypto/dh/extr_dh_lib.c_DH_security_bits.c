#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int length; scalar_t__ p; scalar_t__ q; } ;
typedef  TYPE_1__ DH ;

/* Variables and functions */
 int BN_num_bits (scalar_t__) ; 
 int BN_security_bits (int,int) ; 

int DH_security_bits(const DH *dh)
{
    int N;
    if (dh->q)
        N = BN_num_bits(dh->q);
    else if (dh->length)
        N = dh->length;
    else
        N = -1;
    return BN_security_bits(BN_num_bits(dh->p), N);
}