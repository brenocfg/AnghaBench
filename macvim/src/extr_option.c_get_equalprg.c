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
typedef  scalar_t__ char_u ;
struct TYPE_2__ {scalar_t__* b_p_ep; } ;

/* Variables and functions */
 scalar_t__ NUL ; 
 TYPE_1__* curbuf ; 
 scalar_t__* p_ep ; 

char_u *
get_equalprg()
{
    if (*curbuf->b_p_ep == NUL)
	return p_ep;
    return curbuf->b_p_ep;
}