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
struct TYPE_3__ {scalar_t__ addr; } ;
typedef  TYPE_1__ MEM ;

/* Variables and functions */

__attribute__((used)) static unsigned long mem_hash(const MEM *a)
{
    size_t ret;

    ret = (size_t)a->addr;

    ret = ret * 17851 + (ret >> 14) * 7 + (ret >> 4) * 251;
    return ret;
}