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
struct TYPE_2__ {scalar_t__ vaddr; } ;
struct snic {TYPE_1__ bar0; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 

__attribute__((used)) static void
snic_iounmap(struct snic *snic)
{
	if (snic->bar0.vaddr)
		iounmap(snic->bar0.vaddr);
}