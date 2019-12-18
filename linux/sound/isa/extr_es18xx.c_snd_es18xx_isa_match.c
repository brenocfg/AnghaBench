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
 scalar_t__* enable ; 
 int /*<<< orphan*/  is_isapnp_selected (unsigned int) ; 

__attribute__((used)) static int snd_es18xx_isa_match(struct device *pdev, unsigned int dev)
{
	return enable[dev] && !is_isapnp_selected(dev);
}