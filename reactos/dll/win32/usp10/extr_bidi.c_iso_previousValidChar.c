#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* item; } ;
struct TYPE_4__ {scalar_t__* pcls; } ;
typedef  TYPE_2__ IsolatedRun ;

/* Variables and functions */
 scalar_t__ BN ; 

__attribute__((used)) static inline int iso_previousValidChar(IsolatedRun *iso_run, int index)
{

    if (index <= 0) return -1;
    index --;
    while (index > -1 && *iso_run->item[index].pcls == BN) index--;
    return index;
}