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
struct ioc3_driver_data {TYPE_1__* vma; } ;
struct TYPE_2__ {int /*<<< orphan*/  mcr; } ;

/* Variables and functions */
 unsigned int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nic_wait(struct ioc3_driver_data *idd)
{
	unsigned mcr;

        do {
                mcr = readl(&idd->vma->mcr);
        } while (!(mcr & 2));

        return mcr & 1;
}