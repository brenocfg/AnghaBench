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
typedef  int /*<<< orphan*/  t ;

/* Variables and functions */

__attribute__((used)) static void prefetch256(const void *table)
{
    volatile unsigned long *t=(void *)table,ret;
    unsigned long sum;
    int i;

    /* 32 is common least cache-line size */
    for (sum=0,i=0;i<256/sizeof(t[0]);i+=32/sizeof(t[0]))   sum ^= t[i];

    ret = sum;
}