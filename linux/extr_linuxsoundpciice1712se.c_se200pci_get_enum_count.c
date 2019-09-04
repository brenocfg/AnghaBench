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
struct TYPE_2__ {char** member; } ;

/* Variables and functions */
 TYPE_1__* se200pci_cont ; 

__attribute__((used)) static int se200pci_get_enum_count(int n)
{
	const char * const *member;
	int c;

	member = se200pci_cont[n].member;
	if (!member)
		return 0;
	for (c = 0; member[c]; c++)
		;
	return c;
}