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
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int CS4270_FIRSTREG ; 
 unsigned int CS4270_LASTREG ; 

__attribute__((used)) static bool cs4270_reg_is_readable(struct device *dev, unsigned int reg)
{
	return (reg >= CS4270_FIRSTREG) && (reg <= CS4270_LASTREG);
}