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

/* Variables and functions */
 int has_automatic_cstate_conversion ; 
 scalar_t__ is_bdx (unsigned int,unsigned int) ; 
 scalar_t__ is_skx (unsigned int,unsigned int) ; 

void automatic_cstate_conversion_probe(unsigned int family, unsigned int model)
{
	if (is_skx(family, model) || is_bdx(family, model))
		has_automatic_cstate_conversion = 1;
}