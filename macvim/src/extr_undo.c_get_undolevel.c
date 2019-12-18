#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ b_p_ul; } ;

/* Variables and functions */
 scalar_t__ NO_LOCAL_UNDOLEVEL ; 
 TYPE_1__* curbuf ; 
 long p_ul ; 

__attribute__((used)) static long
get_undolevel()
{
    if (curbuf->b_p_ul == NO_LOCAL_UNDOLEVEL)
	return p_ul;
    return curbuf->b_p_ul;
}