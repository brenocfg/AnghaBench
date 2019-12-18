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
struct davinci_mcasp {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int davinci_mcasp_init_gpiochip(struct davinci_mcasp *mcasp)
{
	return 0;
}